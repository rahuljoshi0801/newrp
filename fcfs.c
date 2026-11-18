#include <stdio.h>
int main() {
  int n, i, j, temp;
  int pid[20], at[20], bt[20], ct[20], tat[20], wt[20];
  float avgTAT = 0, avgWT = 0;
  printf("Enter number of processes: ");
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    pid[i] = i + 1;
    printf("P%d Arrival Time: ", i + 1);
    scanf("%d", &at[i]);
    printf("P%d Burst Time: ", i + 1);
    scanf("%d", &bt[i]);
  }
  // Sort by Arrival Time
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      if (at[i] > at[j]) {
        // swap arrival time
        temp = at[i];
        at[i] = at[j];
        at[j] = temp;
        // swap burst time
        temp = bt[i];
        bt[i] = bt[j];
        bt[j] = temp;
        // swap process id
        temp = pid[i];
        pid[i] = pid[j];
        pid[j] = temp;
      }
    }
  }
  // Calculate Completion Time (CT)
  ct[0] = at[0] + bt[0];
  for (i = 1; i < n; i++) {
    if (at[i] > ct[i - 1]) {
      ct[i] = at[i] + bt[i]; // CPU idle
    } else {
      ct[i] = ct[i - 1] + bt[i];
    }
  }
  // Calculate TAT and WT
  for (i = 0; i < n; i++) {
    tat[i] = ct[i] - at[i];
    wt[i] = tat[i] - bt[i];
    avgTAT += tat[i];
    avgWT += wt[i];
  }
  avgTAT /= n;
  avgWT /= n;
  // Display Table
  printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
  for (i = 0; i < n; i++) {
    printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i],
           wt[i]);
  }
  printf("\nAverage Turnaround Time = %.2f", avgTAT);
  printf("\nAverage Waiting Time = %.2f\n", avgWT);
  return 0;
}
