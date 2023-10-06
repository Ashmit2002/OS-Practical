#include <stdio.h>

// Structure to represent a process
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
};

// Function to find the process with the shortest remaining time
int findShortestRemainingTime(struct Process processes[], int n, int current_time) {
    int min_index = -1;
    int min_remaining_time = 9999;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time < min_remaining_time && processes[i].remaining_time > 0) {
            min_remaining_time = processes[i].remaining_time;
            min_index = i;
        }
    }

    return min_index;
}

// Function to perform SRTF scheduling and calculate turnaround time, waiting time, and completion time
void performSRTFScheduling(struct Process processes[], int n) {
    int completed = 0;
    int current_time = 0;

    while (completed != n) {
        int min_index = findShortestRemainingTime(processes, n, current_time);

        if (min_index == -1) {
            current_time++;
        } else {
            struct Process *p = &processes[min_index];
            printf("Executing Process %d at time %d\n", p->id, current_time);
            p->remaining_time--;
            current_time++;

            if (p->remaining_time == 0) {
                completed++;
                p->completion_time = current_time;
                p->remaining_time = -1; // Mark the process as completed
                printf("Process %d completed at time %d\n", p->id, current_time);
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter the burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nSRTF Scheduling:\n");
    performSRTFScheduling(processes, n);

    // Calculate turnaround time and waiting time
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        struct Process *p = &processes[i];
        int turnaround_time = p->completion_time - p->arrival_time;
        int waiting_time = turnaround_time - p->burst_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p->id, p->arrival_time, p->burst_time, p->completion_time, turnaround_time, waiting_time);
    }

    return 0;
}
