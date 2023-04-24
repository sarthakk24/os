#include <stdio.h>
#include <unistd.h>

int main() {
    execl("./helloworld", "helloworld", NULL);
    printf("This wouldn't print\n");
    return 0;
}

// Algorithm:
// 1. Write a hello world program in c
// 2. Create its binary executable
// 3. In main() function use execl to call the binary file by passing its path
// 4. Complete and execute the main file5.