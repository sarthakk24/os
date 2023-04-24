#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child => PPID: %d PID: %d\n", getppid(), getpid());
        exit(0);
    } else if (pid > 0) {
        printf("Parent => PID: %d\n", getpid());
        printf("Waiting for child process to finish.\n");
        wait(NULL);
        printf("Child process finished.\n");
    } else {
        printf("Unable to create child process.\n");
    }

    return 0;
}

// Algorithm:

// 1. Start the program.
// 2. Declare the pid .
// 3. Initiate the fork process and store it on pid .
// 4. Check If pid is 0 then write a statement to get child process id using getpid().
// 5. Check if pid is greater than zero print parent id using ppid() function .
// 6. Use wait() to wait for the child process to finish .
// 7. Then the child process finished .
// 8. Check if pid<0 then failure in creating a child process .
// 9. Stop the program.