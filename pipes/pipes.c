#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
    int fd[2],n;
    char buffer[100];
    pid_t p;

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    p = fork();
    if (p > 0) {
        printf("Parent Passing value to child\n");
        write(fd[1], "hello\n", 6);
        wait(NULL);
    } else {
        printf("Child printing received value\n");
        n = read(fd[0], buffer, 100);
        write(1, buffer, n);
    }

    return 0;
}

// Algorithm:
// 1. Create a pipe.
// 2. Send a message to the pipe.
// 3. Retrieve the message from the pipe and write it to the standard output.
// 4. Send another message to the pipe.
// 5. Retrieve the message from the pipe and write it to the standard output.