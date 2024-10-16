#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid, at, bt, ct, tat, wt;
};

int compare1(const void *a, const void *b) {
    return ((struct process *)a)->at - ((struct process *)b)->at;
}

int compare2(const void *a, const void *b) {
    return ((struct process *)a)->pid - ((struct process *)b)->pid;
}

int main() {
    int n;
    struct process p[100];
    float avgTat;
    float avgWt;
    int totalTat = 0;
    int totalWt = 0;

    printf("Enter no. of process : ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time of %d processes :\n", n);
    for(int i=0; i<n; i++) {
        printf("AT : ");
        scanf("%d", &p[i].at);
        printf("BT : ");
        scanf("%d", &p[i].bt);
        p[i].pid = i+1;
        printf("\n");
    }

    qsort(p, n, sizeof(struct process), compare1);

    printf("Gantt Chart :\n");
    printf("P%d | ", p[0].pid);
    p[0].ct = p[0].bt;
    p[0].tat = p[0].ct - p[0].at;
    p[0].wt = p[0].tat - p[0].bt;
    totalTat += p[0].tat;
    totalWt += p[0].wt;

    for(int i=1; i<n; i++) {
        printf("P%d | ", p[i].pid);
        if(p[i].at < p[i-1].ct) {
            p[i].ct = p[i-1].ct + p[i].bt;
        } else {
            p[i].ct = p[i].at + p[i].bt;
        }
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalTat += p[i].tat; 
        totalWt += p[i].wt;
    }

    qsort(p, n, sizeof(struct process), compare2);
    
    avgTat = (float)totalTat / n;
    avgWt = (float)totalWt / n;

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\t\n\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAvg. TAT = %.2f\n", avgTat);
    printf("Avg. WT = %.2f\n", avgWt);

    return 0;
}

/*

Enter no. of process : 4
Enter arrival time and burst time of 4 processes :
AT : 0
BT : 2

AT : 1
BT : 2

AT : 5
BT : 3

AT : 6
BT : 4

Gantt Chart :
P1 | P2 | P3 | P4 | 

PID     AT      BT      CT      TAT     WT

1       0       2       2       2       0
2       1       2       4       3       1
3       5       3       8       3       0
4       6       4       12      6       2

Avg. TAT = 3.50
Avg. WT = 0.75

*/
