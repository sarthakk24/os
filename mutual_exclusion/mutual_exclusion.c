#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 2

sem_t mutex;

void* threadFunction(void* arg) {
    int threadId = *(int*)arg;
    
    printf("Thread %d is trying to enter the critical section.\n", threadId);
    
    // Wait for the mutex semaphore
    sem_wait(&mutex);
    
    printf("Thread %d has entered the critical section.\n", threadId);
    
    // Simulating some work inside the critical section
    printf("Thread %d is performing some work.\n", threadId);
    sleep(2);
    
    printf("Thread %d is leaving the critical section.\n", threadId);
    
    // Signal the mutex semaphore to release it
    sem_post(&mutex);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIds[NUM_THREADS];
    
    // Initialize the mutex semaphore
    sem_init(&mutex, 0, 1);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, (void*)&threadIds[i]);
    }
    
    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Destroy the mutex semaphore
    sem_destroy(&mutex);
    
    return 0;
}
