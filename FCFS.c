#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;       // Process ID
    int arrivalTime; // Arrival Time
    int burstTime;  // Burst Time
    int waitingTime; // Waiting Time
    int turnaroundTime; // Turnaround Time
};

// Function to calculate Waiting Time and Turnaround Time
void calculateTimes(struct Process proc[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Calculating waiting time for each process
    proc[0].waitingTime = 0; // Waiting time for the first process is 0
    proc[0].turnaroundTime = proc[0].burstTime; // Turnaround time is same as burst time for first process

    for (int i = 1; i < n; i++) {
        proc[i].waitingTime = proc[i - 1].waitingTime + proc[i - 1].burstTime;
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;
    }

    // Printing the results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
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
    }

    // FCFS assumes processes are executed in order of arrival,
    // so we do not need to sort them if input is already in that order.

    calculateTimes(proc, n);

    return 0;
}
