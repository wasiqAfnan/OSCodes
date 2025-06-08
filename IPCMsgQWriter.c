#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include "mq_com.h"

int main() {
    int msgid;
    char input[1024];

    // Create (or access) a message queue with key 1234 and permissions 0666
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter some text: ");
        fgets(input, sizeof(input), stdin);        // Get input from user

        data.ty = 1;                               // Set message type
        strcpy(data.text, input);                  // Copy input into data.text

        // Send the message to the queue
        if (msgsnd(msgid, (void *)&data, sizeof(data.text), 0) == -1) {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }

        // If input starts with "end", exit loop
        if (strncmp(input, "end", 3) == 0)
            break;
    }

    return 0;
}
