#include <stdio.h>

typedef struct {
    int processID;
    int burstTime;
} Process;

void ljfScheduling(Process proc[], int n) {
    // Sorting processes by burst time in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].burstTime < proc[j].burstTime) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    printf("Process ID\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\n", proc[i].processID, proc[i].burstTime);
    }
}

int main() {
    Process proc[] = {
        {1, 10},
        {2, 5},
        {3, 8}
    };
    int n = sizeof(proc) / sizeof(proc[0]);
    ljfScheduling(proc, n);
    return 0;
}
