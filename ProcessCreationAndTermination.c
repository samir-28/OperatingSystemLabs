#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // This is the parent process
        printf("This is the parent process. PID: %d\n", getpid());
    } else if (pid == 0) {
        // This is the child process
        printf("This is the child process. PID: %d, Parent PID: %d\n", getpid(), getppid());
    } else {
        // Error occurred
        perror("ERROR: Failed to create child process");
        return 1;
    }

    // Both parent and child will execute this part
    printf("Exiting the program. PID: %d\n", getpid());
    return 0;
}
