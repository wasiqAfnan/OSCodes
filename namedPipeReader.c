#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    char message[100];

    // Open the FIFO in read mode
    fd = open("myfifo", O_RDONLY);

    // Read the message from the FIFO
    read(fd, message, sizeof(message));

    // Print the received message
    printf("Received message: %s\n", message);

    // Close the pipe
    close(fd);

    // Remove the pipe after reading (optional)
    unlink("myfifo");

    return 0;
}
