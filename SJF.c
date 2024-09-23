#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;         // Process ID
    int arrivalTime; // Arrival Time
    int burstTime;   // Burst Time
    int waitingTime; // Waiting Time
    int turnaroundTime; // Turnaround Time
    int completionTime; // Completion Time
    int isCompleted; // Flag to check if process is completed
};

// Function to sort processes by arrival time
void sortByArrival(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrivalTime > proc[j].arrivalTime) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to find the waiting time and turnaround time for each process
void calculateTimes(struct Process proc[], int n) {
    int currentTime = 0, completed = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed < n) {
        int idx = -1;
        int minBurstTime = 10000; // Arbitrarily large value

        // Find process with minimum burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !proc[i].isCompleted && proc[i].burstTime < minBurstTime) {
                minBurstTime = proc[i].burstTime;
                idx = i;
            }
        }

        if (idx != -1) {
            proc[idx].completionTime = currentTime + proc[idx].burstTime;
            proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;

            totalWaitingTime += proc[idx].waitingTime;
            totalTurnaroundTime += proc[idx].turnaroundTime;

            currentTime = proc[idx].completionTime;
            proc[idx].isCompleted = 1;
            completed++;
        } else {
            currentTime++;
        }
    }

    // Print the results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].pid = i + 1; // Assigning process ID
        proc[i].isCompleted = 0; // Initializing the completion flag
    }

    // Sort processes by arrival time
    sortByArrival(proc, n);

    // Calculate waiting time and turnaround time
    calculateTimes(proc, n);

    return 0;
}
