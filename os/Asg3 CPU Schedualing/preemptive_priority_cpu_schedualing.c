#include <stdio.h>
#include <string.h>
#include <limits.h>

struct process {
    int pid, prio, at, bt, ct, tat, wt;
};

int main() {
    int n;
    struct process p[100];
    float avgTat;
    float avgWt;
    int totalTat = 0;
    int totalWt = 0;
    int idx;
    int btRem[100];
    int mark[100];
    memset(mark, 0, sizeof(mark));

    printf("Enter no. of process : ");
    scanf("%d", &n);

    printf("Enter priority, arival time and burst time of %d processes :\n", n);
    for(int i=0; i<n; i++) {
        printf("Prio : ");
        scanf("%d", &p[i].prio);
        printf("AT : ");
        scanf("%d", &p[i].at);
        printf("BT : ");
        scanf("%d", &p[i].bt);
        btRem[i] = p[i].bt;
        p[i].pid = i+1;
        printf("\n");
    }

    int currTime = 0;
    int completed = 0;

    printf("Gantt Chart :\n");
    while(completed != n) {
        idx = -1;
        int mx = INT_MIN;

        for(int i=0; i<n; i++) {
            if(p[i].at <= currTime && mark[i] == 0) {
                if(p[i].prio > mx) {
                    mx = p[i].prio;
                    idx = i;
                }

                if(btRem[i] == mx) {
                    if(p[i].at < p[idx].at) {
                        mx = p[i].prio;
                        idx = i;
                    }
                    
                }
            }            
        }

        if(idx != -1) {
            printf("P%d | ", p[idx].pid);
            btRem[idx] -= 1;
            currTime++;

            if(btRem[idx] == 0) {
                p[idx].ct = currTime;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                totalTat += p[idx].tat; 
                totalWt += p[idx].wt;

                mark[idx] = 1;
                completed++;
            }
        } else {
            currTime++;
        }
    }

    avgTat = (float)totalTat / n;
    avgWt = (float)totalWt / n;

    printf("\n\nPRIO\tPID\tAT\tBT\tCT\tTAT\tWT\t\n\n");
    for(int i=0; i<n; i++) {
        printf(" %d\t%d\t%d\t%d\t%d\t%d\t%d\t\n", p[i].prio, p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAvg. TAT = %.2f\n", avgTat);
    printf("Avg. WT = %.2f\n", avgWt);

    return 0;
}

/*

Enter no. of process : 4
Enter priority, arival time and burst time of 4 processes :
Prio : 10
AT : 0
BT : 5

Prio : 20
AT : 1
BT : 4

Prio : 30
AT : 2
BT : 2

Prio : 40
AT : 4
BT : 1

Gantt Chart :
P1 | P2 | P3 | P3 | P4 | P2 | P2 | P2 | P1 | P1 | P1 | P1 | 

PRIO    PID     AT      BT      CT      TAT     WT

 10     1       0       5       12      12      7
 20     2       1       4       8       7       3
 30     3       2       2       4       2       0
 40     4       4       1       5       1       0

Avg. TAT = 5.50
Avg. WT = 2.50

*/
