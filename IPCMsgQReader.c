#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include "mq_com.h"

int main() {
    int msgid;

    // Access the message queue with the same key
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Receive a message of any type (0), store in data
        if (msgrcv(msgid, (void *)&data, sizeof(data.text), 0, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }

        printf("You wrote: %s", data.text);

        // If message starts with "end", stop receiving
        if (strncmp(data.text, "end", 3) == 0)
            break;
    }

    // Delete the message queue after communication ends
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl (remove queue) failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
