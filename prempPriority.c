#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int remainingTime;
};

int findHighestPriority(struct Process processes[], int n, int currentTime) {
    int highestPriority = -1;
    int highestPriorityProcessIndex = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
            if (highestPriority == -1 || processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                highestPriorityProcessIndex = i;
            }
        }
    }

    return highestPriorityProcessIndex;
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0.0;
    float totalTurnaroundTime = 0.0;

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\n");

    while (completed < n) {
        int highestPriorityProcessIndex = findHighestPriority(processes, n, currentTime);

        if (highestPriorityProcessIndex == -1) {
            currentTime++;
        } else {
            struct Process *currentProcess = &processes[highestPriorityProcessIndex];
            currentProcess->remainingTime--;

            if (currentProcess->remainingTime == 0) {
                currentProcess->completionTime = currentTime + 1;
                currentProcess->waitingTime = currentProcess->completionTime - currentProcess->arrivalTime - currentProcess->burstTime;
                totalWaitingTime += currentProcess->waitingTime;
                totalTurnaroundTime += currentProcess->completionTime - currentProcess->arrivalTime;
                completed++;
            }

            currentTime++;
        }
    }

    float averageWaitingTime = totalWaitingTime / n;
    float averageTurnaroundTime = totalTurnaroundTime / n;
    float cpuUtilization = (totalTurnaroundTime / currentTime) * 100;

    printf("\nAverage Waiting Time: %.2f", averageWaitingTime);
    printf("\nAverage Turnaround Time: %.2f", averageTurnaroundTime);
    printf("\nCPU Utilization: %.2f%%\n", cpuUtilization);

    return 0;
}
