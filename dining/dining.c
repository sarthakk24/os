#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
sem_t mutex;
sem_t S[N];

void test(int phnum)
{
    if (state[phnum] == HUNGRY &&
        state[LEFT] != EATING &&
        state[RIGHT] != EATING)
    {
        state[phnum] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n",
            phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        sem_post(&S[phnum]);
    }
}

void take_fork(int phnum)
{
    sem_wait(&mutex);
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);
    test(phnum);
    sem_post(&mutex);
    sem_wait(&S[phnum]);
    sleep(1);
}

void put_fork(int phnum)
{
    sem_wait(&mutex);
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n",
        phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void* num)
{
    while (1)
    {
        int* i = num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}

int main()
{
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);
    for (i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}


// Algorithm:
// 1. The dining philosophers problem states that there are 5 philosophers sharing a circular
// table and they eat and think alternatively. There is a bowl of rice for each of the
// philosophers and 5 chopsticks. A philosopher needs both their right and left chopstick to
// eat. A hungry philosopher may only eat if there are both chopsticks available. Otherwise,
// a philosopher puts down their chopstick and begins thinking again.
// 2. A solution of the Dining Philosophers Problem is to use a semaphore to represent a
// chopstick. A chopstick can be picked up by executing a wait operation on the semaphore
// and released by executing a signal semaphore.
// 3. Initially the chopsticks are initialized to 1 as the chopsticks are on the table and not
// picked up by a philosopher
// 4. First wait operation is performed on chopstick[i] and chopstick[(i+1)%5]. This means that
// the philosopher i has picked up the chopsticks on his sides. Then the eating functionis
// performed.
// 5. After that, signal operation is performed on chopstick[i] and chopstick[(i+1)%5]. This
// means that the philosopher I has eaten and put down the chopsticks on his sides. Then
// thephilosopher goes back to thinking.