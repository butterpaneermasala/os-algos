#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Number of philosophers
#define N 5

// Mutexes for forks
pthread_mutex_t forks[N];

// Function for philosopher's behavior
void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1); // Simulate thinking

        // Picking up forks: Odd philosophers pick the left fork first, then the right; even philosophers do the opposite
        if (id % 2 == 0) {
            pthread_mutex_lock(&forks[(id + 1) % N]); // Pick up right fork
            pthread_mutex_lock(&forks[id]);           // Pick up left fork
        } else {
            pthread_mutex_lock(&forks[id]);           // Pick up left fork
            pthread_mutex_lock(&forks[(id + 1) % N]); // Pick up right fork
        }

        printf("Philosopher %d is eating...\n", id);
        sleep(1); // Simulate eating

        // Put down forks
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % N]);

        printf("Philosopher %d finished eating and put down forks.\n", id);
    }
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize mutexes for forks
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for philosopher threads to finish (they never will in this case)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
