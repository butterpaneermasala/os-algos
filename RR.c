#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;          // Process ID
    int arrivalTime;  // Arrival Time
    int burstTime;    // Burst Time
    int remainingTime; // Remaining Time (for Round Robin)
    int waitingTime;  // Waiting Time
    int turnaroundTime; // Turnaround Time
};

// Function to perform Round Robin Scheduling
void roundRobin(struct Process proc[], int n, int timeQuantum) {
    int currentTime = 0;
    int completed = 0;
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0) {
                if (proc[i].remainingTime > timeQuantum) {
                    currentTime += timeQuantum;
                    proc[i].remainingTime -= timeQuantum;
                } else {
                    currentTime += proc[i].remainingTime;
                    proc[i].remainingTime = 0;
                    completed++;

                    proc[i].turnaroundTime = currentTime - proc[i].arrivalTime;
                    proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;

                    totalWaitingTime += proc[i].waitingTime;
                    totalTurnaroundTime += proc[i].turnaroundTime;
                }
            }
        }
    }

    // Print the results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].pid = i + 1; // Assigning process ID
        proc[i].remainingTime = proc[i].burstTime; // Initially, remaining time is the burst time
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    // Perform Round Robin Scheduling
    roundRobin(proc, n, timeQuantum);

    return 0;
}
