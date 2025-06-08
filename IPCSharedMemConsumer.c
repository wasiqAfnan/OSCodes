#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"

int main() {
    int shmid;
    void *shared_memory;
    struct sm *sh;

    // Get existing shared memory
    shmid = shmget((key_t)34, sizeof(struct sm), 0666);
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
        if (sh->wr == 1) {
            printf("Message from producer: %s", sh->st);
            sh->wr = 0;

            if (strncmp(sh->st, "end", 3) == 0)
                break;
        }
        sleep(1); // Avoid CPU overuse
    }

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL); // Remove shared memory

    return 0;
}
