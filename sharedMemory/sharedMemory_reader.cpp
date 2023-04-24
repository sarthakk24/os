#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
using namespace std;

int main() {
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);
    printf("Data written in memory: %s\n", str);
    shmdt(str);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}

// Algorithm For Reader Code
// 1. Get the key of shared memory using ftok command.
// 2. Store the shmid that you get from shmget command using the key .
// 3. Get the string that was previously written in memory .
// 4. Use the shmdt command to pan the shmid .
// 5. Exit the program.