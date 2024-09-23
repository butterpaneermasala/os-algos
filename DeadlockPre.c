#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

// Function to check if resources can be allocated based on resource ordering
bool canAllocate(int need[][NUM_RESOURCES], int available[], int process) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (need[process][i] > available[i]) {
            return false;
        }
    }
    return true;
}

// Function to simulate resource allocation
void allocateResources(int allocation[][NUM_RESOURCES], int available[], int process) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] -= allocation[process][i];
    }
}

// Function to release allocated resources
void releaseResources(int allocation[][NUM_RESOURCES], int available[], int process) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] += allocation[process][i];
    }
}

int main() {
    int available[NUM_RESOURCES] = {3, 3, 2}; // Available resources
    int max[NUM_PROCESSES][NUM_RESOURCES] = {
        {7, 5, 3}, // Max resources for process 0
        {3, 2, 2}, // Max resources for process 1
        {9, 0, 2}, // Max resources for process 2
        {2, 2, 2}, // Max resources for process 3
        {4, 3, 3}  // Max resources for process 4
    };

    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
        {0, 1, 0}, // Resources allocated to process 0
        {2, 0, 0}, // Resources allocated to process 1
        {3, 0, 2}, // Resources allocated to process 2
        {2, 1, 1}, // Resources allocated to process 3
        {0, 0, 2}  // Resources allocated to process 4
    };

    int need[NUM_PROCESSES][NUM_RESOURCES]; // Resources still needed by each process

    // Calculate the need matrix
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    bool finish[NUM_PROCESSES] = {false}; // Track finished processes
    int safeSequence[NUM_PROCESSES]; // Store the safe sequence
    int count = 0;

    // Deadlock prevention: Resource Ordering
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_PROCESSES; j++) {
            if (!finish[j] && canAllocate(need, available, j)) {
                // Process can allocate the needed resources
                allocateResources(allocation, available, j);
                safeSequence[count++] = j;
                finish[j] = true;
            }
        }
    }

    // Check if all processes are finished
    bool allFinished = true;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            allFinished = false;
            break;
        }
    }

    if (allFinished) {
        printf("System is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < NUM_PROCESSES; i++) {
            printf("%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("System is not in a safe state.\n");
    }

    return 0;
}
