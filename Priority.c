#include <stdio.h>

typedef struct {
    int processID;
    int burstTime;
    int priority;
} Process;

void priorityScheduling(Process proc[], int n) {
    // Sorting processes by priority
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority < proc[j].priority) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    printf("Process ID\tBurst Time\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", proc[i].processID, proc[i].burstTime, proc[i].priority);
    }
}

int main() {
    Process proc[] = {
        {1, 10, 2},
        {2, 5, 1},
        {3, 8, 3}
    };
    int n = sizeof(proc) / sizeof(proc[0]);
    priorityScheduling(proc, n);
    return 0;
}