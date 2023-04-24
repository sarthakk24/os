#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 50

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main() {
    key_t key;
    int msgid;
    
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    message.mesg_type = 1;
    printf("Write Data:");
    fgets(message.mesg_text, MAX, stdin);

    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Data sent is: %s\n", message.mesg_text);

    return 0;
}

// Algorithm for Write Code
// 1. Create a structure for the message queue to take in the message and store it.
// 2. Initiate a variable key_t and store ftok and its path.
// 3. Using msgget create a message queue and return the identifier.
// 4. Use str to input data.
// 5. Write a message into the string using mesg_text.
// 6. Send a message using msgsnd .
// 7. End Program .