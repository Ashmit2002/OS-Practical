#include<stdio.h>
struct process{
    int id;
    int ct;
    int remT;
    int bt;
    int at;
};
int findShortestRemainingTime(struct process p[],int n,int current_time){
    int min_index=-1;
    int min_remaining_time=9999;
    for(int i =0 ;i<n;i++)
    {
        if(p[i].at<=current_time && p[i].remT<min_remaining_time && p[i].remT>0){
            min_remaining_time=p[i].remT;
            min_index=i;
        }
    }
    return min_index;
}
void performSRTF(struct process p[],int n)
{
    int complete=0;
    int current_time=0;
    while(complete!=n)
    {
        int min_index=findShortestRemainingTime(p,n,current_time);
        if(min_index==-1)
        {
            current_time++;
        }
        else{
            struct process *pro=&p[min_index];
            printf("Executing process %d at time %d\n",pro->id,current_time);
            pro->remT--;
            current_time++;
            
            if(pro->remT==0)
            {
                complete++;
                pro->ct=current_time;
                pro->remT=-1;
                printf("process %d completed at time %d\n",pro->id,current_time);
            }

        }
    }
}

int main()
{
    int n;
    printf("Enter the No of Process: ");
    scanf("%d",&n);
    struct process p[n];
    int total_turnaround_time=0;
    int total_waiting_time=0;
    for(int i=0;i<n;i++)
    {
        printf("Enter the Arrival Time for process P%d: ",i+1);
        scanf("%d",&p[i].at);
        printf("Enter the Burst Time for process P%d:",i+1);
        scanf("%d",&p[i].bt);
        p[i].id=i+1;
        p[i].remT=p[i].bt;
    }

    printf("___SRTF SCHEDULING___");
    performSRTF(p,n);

    printf("\nProcessID\t Arrival Time\t BurstTime\t Completion Time\t Tat\t Waiting Time\n");
    for(int i=0;i<n;i++)
    {
        struct process *pr = &p[i];
        int turnaround_time = pr->ct - pr->at;
        int waiting_time = turnaround_time - pr->bt;
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pr->id, pr->at, pr->bt, pr->ct,turnaround_time, waiting_time);
    }
    float average_waiting_time = (float)total_waiting_time / n;
    float average_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
    return 0;
}