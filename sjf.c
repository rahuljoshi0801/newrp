#include <stdio.h>
#define MAX 20
//Non-Preemptive SJF
void sjfNonPreemptive() {
    int n, i, j;
    int pid[MAX], at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX], completed[MAX];
    int time = 0, count = 0, min_bt, idx;
    float avgTAT = 0, avgWT = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        completed[i] = 0;
    }
    while (count < n) {
        min_bt = 9999;
        idx = -1;
        // find process with smallest burst time among arrived
        for (i = 0; i < n; i++) {
            if (at[i] <= time && completed[i] == 0) {
                if (bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                } else if (bt[i] == min_bt) {
                    if (at[i] < at[idx]) idx = i;
                }
            }
        }
        if (idx != -1) {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            avgTAT += tat[idx];
            avgWT += wt[idx];
            completed[idx] = 1;
            count++;
        } else {
            time++; // CPU idle
        }
    }
    printf("\n--- Non-Preemptive SJF (SJFNP) ---\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Turnaround Time = %.2f", avgTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", avgWT / n);
}
//Preemptive SJF (SRTF)
void sjfPreemptive() {
    int n, i, time = 0, min, idx;
    int at[MAX], bt[MAX], rt[MAX], ct[MAX], tat[MAX], wt[MAX], completed[MAX] = {0};
    float avg_tat = 0, avg_wt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter Arrival time of P%d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst time of P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // initialize remaining time
    }
    int completed_count = 0;
    while (completed_count < n) {
        min = 9999;
        idx = -1;
        // find process with minimum remaining time
        for (i = 0; i < n; i++) {
            if (at[i] <= time && completed[i] == 0) {
                if (rt[i] < min) {
                    min = rt[i];
                    idx = i;
                } else if (rt[i] == min) {
                    if (at[i] < at[idx]) idx = i;
                }
            }
        }
        if (idx != -1) {
            rt[idx]--;
            time++;
            if (rt[idx] == 0) {
                completed[idx] = 1;
                completed_count++;
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
            }
        } else {
            time++;
        }
    }
    printf("\n--- Preemptive SJF (SRTF) ---\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);
}
int main() {
    int choice;
    printf("Choose Scheduling Type:\n");
    printf("1. Non-Preemptive SJF (SJFNP)\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 1) {
        sjfNonPreemptive();
    } else if (choice == 2) {
        sjfPreemptive();
    } else {
        printf("Invalid choice!\n");
    }
    return 0;
}

