#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep()

#define BUFFER_SIZE 10

// Shared buffer and indices
int buffer[BUFFER_SIZE];
int in = 0;    // Index for producer
int out = 0;   // Index for consumer

// Semaphores and mutex
sem_t empty;   // Semaphore to count empty slots
sem_t full;    // Semaphore to count full slots
pthread_mutex_t mutex; // Mutex for mutual exclusion

// Producer function
void* producer(void* arg) {
    while (1) {
        int item = rand() % 100; // Produce a random item
        sem_wait(&empty);        // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced: %d\n", item);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);             // Signal that buffer has a new item

        sleep(1); // Simulate time taken to produce an item
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);             // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Remove item from buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed: %d\n", item);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);            // Signal that buffer has an empty slot

        sleep(2); // Simulate time taken to consume an item
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full, 0, 0);            // Initially, no slots are full
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish (they run indefinitely in this example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Cleanup (not reached in this example, but good practice)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
