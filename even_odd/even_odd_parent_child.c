#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
    int pid, num_values, i;
    printf("Enter the number of values: ");
    scanf("%d", &num_values);

    int values[num_values];
    printf("Enter %d values:\n", num_values);
    for(i = 0; i < num_values; i++) {
        scanf("%d", &values[i]);
    }

    pid = fork();
    if(pid == 0) {
        // Child process prints odd values
        printf("Odd Values: \n");
        for(i = 0; i < num_values; i++) {
            if (values[i] % 2 != 0) {
                printf("%d\t", values[i]);
            }
        }
    } else {
        // Parent process prints even values
        wait(NULL);
        printf("\nEven Values: \n");
        for (i = 0; i < num_values; i++) {
            if (values[i] % 2 == 0) {
                printf("%d\t", values[i]);
            }
        }
        printf("\n");
    }
    return 0;
}

// Algorithm:
// 1. Use fork() function to create one child and one parent process
// 2. For child process , fork() returns 0
// 3. So we calculate sum of all odd numbers
// 4. Fork() returns value greater than 0 for parent process
// 5. So we calculate sum of even numbers
// 6. We do so by just checking the value returned by fork() command