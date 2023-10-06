#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int id;            // Process ID
    int bt;    // Burst time (time needed to complete)
    int rt; // Remaining time to complete
    int at;  // Arrival time of the process
    int ct; // Completion time of the process
    int tat; // Turnaround time of the process
    int wt;   // Waiting time of the process
};

// Function to perform round robin scheduling
void roundRobin(struct Process p[], int n, int quantum) {
    int remaining_processes = n;
    int current_time = 0;
    int cpu_utilization_time = 0; // Track CPU utilization time

    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= current_time) {
                int execution_time = (p[i].rt < quantum) ? p[i].rt : quantum;

                p[i].rt -= execution_time;
                current_time += execution_time;
                cpu_utilization_time += execution_time; // Increment CPU utilization time

                if (p[i].rt == 0) {
                    p[i].ct = current_time;
                    remaining_processes--;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
            }
        }
    }

    // Calculate CPU utilization percentage
    float cpu_utilization = ((float)cpu_utilization_time / current_time) * 100.0;
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
}

int main() {
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter quantum time: ");
    scanf("%d", &quantum);

    
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].id = i + 1;
        p[i].rt = p[i].bt;
        p[i].ct = 0; // Initialize completion time to 0
        p[i].tat = 0; // Initialize turnaround time to 0
        p[i].wt = 0;   // Initialize waiting time to 0
    }

    printf("\nRound Robin Scheduling:\n");
    roundRobin(p, n, quantum);

    // Calculate and display average turnaround time, waiting time, and CPU utilization
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        total_turnaround_time += p[i].tat;
        total_waiting_time += p[i].wt;
    }

    double average_turnaround_time = (double)total_turnaround_time / n;
    double average_waiting_time = (double)total_waiting_time / n;
    
    // Display the tabular form
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Display average turnaround time, waiting time, and CPU utilization
    printf("\nAverage Turnaround Time: %.2lf\n", average_turnaround_time);
    printf("Average Waiting Time: %.2lf\n", average_waiting_time);
   
    return 0;
}
