#include <stdio.h>
#include <unistd.h>

void main() {
    int pid;

    pid = fork();
    if (pid == 0) {
        printf("Child process: Running Hello World Program\n");
        execl("./helloworld", "./helloworld", (char *)0);
        printf("This wouldn't print\n");
    }
    else {
        sleep(3);
        printf("Parent process: Running While loop Program\n");
        execl("./while_loop", "./while_loop", (char *)0);
        printf("Won't reach here\n");
    }
}

// Algorithm:
// 1. Write a hello_world and while_loop program in c
// 2. Use excel to call these files
// 3. But in one process we can use fork to create child and parent
// 4. In child call hello_world
// 5. In parent call while_loop