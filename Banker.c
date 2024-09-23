#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int numProcesses, int numResources) {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafe(int processes[], int available[], int max[][MAX_RESOURCES], int allocation[][MAX_RESOURCES], int numProcesses, int numResources) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, max, allocation, numProcesses, numResources);

    int finished[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];

    for (int i = 0; i < numResources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < numProcesses) {
        int found = 0;
        for (int p = 0; p < numProcesses; p++) {
            if (finished[p] == 0) {
                int j;
                for (j = 0; j < numResources; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == numResources) {
                    for (int k = 0; k < numResources; k++) {
                        work[k] += allocation[p][k];
                    }
                    safeSequence[count++] = p;
                    finished[p] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < numProcesses; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    int numProcesses, numResources;
    int allocation[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES], available[MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    int processes[MAX_PROCESSES];
    for (int i = 0; i < numProcesses; i++) {
        processes[i] = i;
    }

    isSafe(processes, available, max, allocation, numProcesses, numResources);

    return 0;
}
