#include <stdio.h>
#include <string.h>
#include <limits.h>

struct process {
    int pid, at, bt, ct, tat, wt;
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

    printf("Enter arival time and burst time of %d processes :\n", n);
    for(int i=0; i<n; i++) {
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
        int mn = INT_MAX;

        for(int i=0; i<n; i++) {
            if(p[i].at <= currTime && mark[i] == 0) {
                if(btRem[i] < mn) {
                    mn = btRem[i];
                    idx = i;
                }

                if(btRem[i] == mn) {
                    if(p[i].at < p[idx].at) {
                        mn = btRem[i];
                        idx = i;
                    }
                    
                }
            }            
        }

        if(idx != -1) {
            printf("P%d | ", p[idx].pid);
            p[idx].ct = currTime + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            totalTat += p[idx].tat; 
            totalWt += p[idx].wt;
            mark[idx] = 1;

            completed++;
            currTime = p[idx].ct;
        } else {
            currTime++;
        }
    }
    
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
Enter arival time and burst time of 4 processes :
AT : 1
BT : 3

AT : 2
BT : 4

AT : 1
BT : 2

AT : 4
BT : 4

Gantt Chart :
P3 | P1 | P2 | P4 | 

PID     AT      BT      CT      TAT     WT

1       1       3       6       5       2
2       2       4       10      8       4
3       1       2       3       2       0
4       4       4       14      10      6

Avg. TAT = 6.25
Avg. WT = 3.00

*/
