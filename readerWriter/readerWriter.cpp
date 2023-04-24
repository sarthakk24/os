#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

class Monitor {
private:
    int rcnt;
    int wcnt;
    int waitr;
    int waitw;
    pthread_cond_t canread;
    pthread_cond_t canwrite;
    pthread_mutex_t condlock;

public:
    Monitor() {
        rcnt = 0;
        wcnt = 0;
        waitr = 0;
        waitw = 0;
        pthread_cond_init(&canread, NULL);
        pthread_cond_init(&canwrite, NULL);
        pthread_mutex_init(&condlock, NULL);
    }

    void beginread(int i) {
        pthread_mutex_lock(&condlock);
        if (wcnt == 1 || waitw > 0) {
            waitr++;
            pthread_cond_wait(&canread, &condlock);
            waitr--;
        }
        rcnt++;
        cout << "reader " << i << " is reading\n";
        pthread_mutex_unlock(&condlock);
        pthread_cond_broadcast(&canread);
    }

    void endread(int i) {
        pthread_mutex_lock(&condlock);
        if (--rcnt == 0)
            pthread_cond_signal(&canwrite);
        pthread_mutex_unlock(&condlock);
    }

    void beginwrite(int i) {
        pthread_mutex_lock(&condlock);
        if (wcnt == 1 || rcnt > 0) {
            ++waitw;
            pthread_cond_wait(&canwrite, &condlock);
            --waitw;
        }
        wcnt = 1;
        cout << "writer " << i << " is writing\n";
        pthread_mutex_unlock(&condlock);
    }

    void endwrite(int i) {
        pthread_mutex_lock(&condlock);
        wcnt = 0;
        if (waitr > 0)
            pthread_cond_signal(&canread);
        else
            pthread_cond_signal(&canwrite);
        pthread_mutex_unlock(&condlock);
    }
} M;

void* reader(void* id) {
    int c = 0;
    int i = *(int*)id;
    while (c < 5) {
        usleep(1);
        M.beginread(i);
        M.endread(i);
        c++;
    }
}

void* writer(void* id) {
    int c = 0;
    int i = *(int*)id;
    while (c < 5) {
        usleep(1);
        M.beginwrite(i);
        M.endwrite(i);
        c++;
    }
}

int main() {
    pthread_t r[5], w[5];
    int id[5];
    for (int i = 0; i < 5; i++) {
        id[i] = i;
        pthread_create(&r[i], NULL, &reader, &id[i]);
        pthread_create(&w[i], NULL, &writer, &id[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(w[i], NULL);
    }
}

// Algorithm:
// 1. Used for time sharing systems
// 2. Pre-emption is added which enables system to switch between processes.
// 3. A fixed time is allotted to each process, called quantum, for execution.
// 4. A process is executed for the given time period that process us pre-empted and another
// process executes for the given time period.
// 5. Context switching is used to save states of pre-empted processes.
// 6. Enter total number of processes, enter their arrival time and burst time.
// 7. Enter the time quantum for each process.
// 8. Print the burst time, waiting time for each process.
// 9. Calculate and print the total waiting time and total turnaround time.