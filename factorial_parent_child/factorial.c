#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int sumOfDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int main() {
    int number;
    printf("Enter a positive integer: ");
    scanf("%d", &number);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        // Error occurred during forking
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        int fact = factorial(number);
        printf("Factorial of %d is: %d\n", number, fact);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int sum = sumOfDigits(number);
            printf("Sum of digits of %d is: %d\n", number, sum);
        }
    }
    
    return 0;
}
