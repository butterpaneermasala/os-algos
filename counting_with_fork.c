#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Create a child process using fork
    pid = fork();

    if (pid < 0) {
        // If fork() returns a negative value, it indicates a failure to fork
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        // This block is executed by the child process
        printf("Child Process:\n");
        for (int i = 1; i <= 5; i++) {
            printf("Child PID: %d, Number: %d\n", getpid(), i);
            sleep(1); // Introduce a small delay for clearer interleaving
        }
    } else {
        // This block is executed by the parent process
        printf("Parent Process:\n");
        for (int i = 1; i <= 5; i++) {
            printf("Parent PID: %d, Number: %d\n", getpid(), i);
            sleep(1); // Introduce a small delay for clearer interleaving
        }
    }

    return 0;
}
