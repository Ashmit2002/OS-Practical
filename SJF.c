#include <stdio.h>

// Function to find the waiting time for each process
void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = bt[i];
    }

    int completed = 0;
    int current_time = 0;
    int min_index;

    while (completed != n) {
        min_index = -1;
        int min_bt = 9999;

        // Find the process with the shortest remaining burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining_time[i] < min_bt && remaining_time[i] > 0) {
                min_bt = remaining_time[i];
                min_index = i;
            }
        }

        // If no process is found, increment the current time
        if (min_index == -1) {
            current_time++;
        } else {
            // Process found, update waiting time, current time, and mark the process as completed
            wt[min_index] = current_time - at[min_index];
            remaining_time[min_index] = 0;
            current_time += bt[min_index];
            completed++;
        }
    }
}

// Function to find the turnaround time for each process
void findTurnaroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to find the average waiting time and average turnaround time
void findAverageTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], ct[n];

    findWaitingTime(processes, n, bt, wt, at);
    findTurnaroundTime(processes, n, bt, wt, tat);

    // Calculate completion time
    ct[0] = at[0] + tat[0];
    for (int i = 1; i < n; i++) {
        ct[i] = ct[i - 1] + tat[i];
    }

    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    float average_wt = total_wt / n;
    float average_tat = total_tat / n;

    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], bt[i], at[i], wt[i], tat[i], ct[i]);
    }

    printf("Average Waiting Time: %.2f\n", average_wt);
    printf("Average Turnaround Time: %.2f\n", average_tat);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time for Process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Enter the burst time for Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1;
    }

    findAverageTime(processes, n, burst_time, arrival_time);

    return 0;
}