#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct mesg_buffer {
    long mesg_type;
    char msg_text[100];
} message;

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Data received is: %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}

// Algorithm for Read code
// 1. Get the key using ftok command.
// 2. use msgget to create a message queue and return the identifier .
// 3. Get the string that was previously written and print it using msgrcv.
// 4. Destroy the message queue using msgctl.
// 5. End program.