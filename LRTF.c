#include <stdio.h>
#include <stdbool.h>

struct process {
    int id;
    int ct;
    int remT;
    int bt;
    int at;
    int started_time; // Track when the process started
};

int findLongestRemainingTime(struct process p[], int n, int current_time) {
    int max_index = -1;
    int max_remaining_time = -1;

    for (int i = 0; i < n; i++) {
        if (p[i].at <= current_time && p[i].remT > max_remaining_time && p[i].remT > 0) {
            max_remaining_time = p[i].remT;
            max_index = i;
        }
    }

    return max_index;
}

void performLRTF(struct process p[], int n) {
    int complete = 0;
    int current_time = 0;
    int cpu_utilization_time = 0; // Track CPU utilization time

    while (complete != n) {
        int max_index = findLongestRemainingTime(p, n, current_time);

        if (max_index == -1) {
            current_time++;
        } else {
            struct process *pro = &p[max_index];

            // Check if the process just started execution, and update the started_time
            if (pro->remT == pro->bt) {
                pro->started_time = current_time;
            }

            // printf("Executing process %d at time %d\n", pro->id, current_time);
            pro->remT--;
            current_time++;
            cpu_utilization_time++; // Increment CPU utilization time

            if (pro->remT == 0) {
                complete++;
                pro->ct = current_time;
                pro->remT = -1;
                // printf("Process %d completed at time %d\n", pro->id, current_time);
            }
        }
    }

    // Calculate CPU utilization percentage
    float cpu_utilization = ((float)cpu_utilization_time / current_time) * 100.0;
    printf("CPU Utilization: %.2f%%\n", cpu_utilization);
}

int main() {
    int n;
    printf("Enter the No of Process: ");
    scanf("%d", &n);
    struct process p[n];
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter the Arrival Time for process P%d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter the Burst Time for process P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].id = i + 1;
        p[i].remT = p[i].bt;
    }

    printf("___LRTF SCHEDULING___\n");
    performLRTF(p, n);

    printf("\nProcessID\tArrival Time\tBurstTime\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        struct process *pr = &p[i];
        int turnaround_time = pr->ct - pr->at;
        int waiting_time = turnaround_time - pr->bt;
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t %d\t\t%d\n", pr->id, pr->at, pr->bt, pr->ct, turnaround_time, waiting_time);
    }

    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}
