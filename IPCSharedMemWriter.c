#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include "shm_com.h"

int main() {
    int shmid;
    void *shared_memory;
    struct sm *sh;
    char buffer[2048];
    // Create shared memory
    shmid = shmget((key_t)34, sizeof(struct sm), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    // Attach to shared memory
    shared_memory = shmat(shmid, NULL, 0);
    if (shared_memory == (void *) -1) {
        perror("shmat failed");
        exit(1);
    }
    sh = (struct sm *)shared_memory;
    while (1) {
        // Wait if previous message not read yet
        while (sh->wr == 1) {
            printf("Waiting for consumer...\n");
            sleep(1);
        }
        printf("Enter message: ");
        fgets(buffer, 2048, stdin);
        strncpy(sh->st, buffer, 2048);
        sh->wr = 1;  // Signal message is ready
        // Exit condition
        if (strncmp(buffer, "end", 3) == 0)
            break;
    }
    shmdt(shared_memory);
    return 0;
}
