#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefds[2]; // pipefds[0] = read end, pipefds[1] = write end
    char message[100];
    char buffer[100];
    pid_t pid;
    int bytes_read;

    fflush(stdin);
    printf("Enter message: ");
    fflush(stdout);
    // Read input from keyboard using file descriptor 0 (stdin)
    bytes_read = read(0, message, sizeof(message));

    // Replace newline with '\0'
    message[bytes_read - 1] = '\0';

    // Create pipe
    if (pipe(pipefds) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork the process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process: read from pipe
        close(pipefds[1]);  // Close write end
        read(pipefds[0], buffer, sizeof(buffer));
        printf("Child (PID %d) read: %s\n", getpid(), buffer);
        close(pipefds[0]);  // Close read end
    } else {
        // Parent process: write to pipe
        close(pipefds[0]);  // Close read end
        write(pipefds[1], message, strlen(message) + 1);  // +1 to include null terminator
        printf("Parent (PID %d) wrote: %s\n", getpid(), message);
        close(pipefds[1]);  // Close write end
    }

    return 0;
}
