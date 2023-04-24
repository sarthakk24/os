#include <iostream>
#include <cstdio>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    if(shmid == -1) {
        perror("shmget failed");
        return 1;
    }
    char *str = (char*) shmat(shmid, (void*)0, 0);
    cout << "Write data: ";
    cin >> str;
    printf("Data written in memory: %s", str);
    shmdt(str);
    return 0;
}

// Algorithm Writer Code:
// 1. Initiate a variable key_t and store ftok and its path where to store .
// 2. Using shmget , store the generated id in shmid .
// 3. Using str take input .
// 4. Write the string in str .
// 5. End the Program.