#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    char message[100];

    // Create the named pipe (only once)
    mkfifo("myfifo", 0666);

    // Ask the user to enter some text
    printf("Enter message to send: ");
    fflush(stdout);
    int byteRead=read(0, message, sizeof(message));  // Read from keyboard

    message[byteRead-1]='\0';

    // Open the FIFO in write mode
    fd = open("myfifo", O_WRONLY);

    // Write the message into the FIFO
    write(fd, message, sizeof(message));

    // Close the pipe
    close(fd);

    return 0;
}
