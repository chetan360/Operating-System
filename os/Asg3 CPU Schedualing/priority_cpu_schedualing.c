#include <stdio.h>
#include <string.h>
#include <limits.h>

struct process {
    int prio, pid, at, bt, ct, tat, wt;
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
        printf("PRIO : ");
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
                        mx = btRem[i];
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
Enter arival time and burst time of 4 processes :
PRIO : 3
AT : 0
BT : 8

PRIO : 4
AT : 1
BT : 2

PRIO : 4
AT : 3
BT : 4

PRIO : 5
AT : 4
BT : 1

Gantt Chart :
P1 | P4 | P2 | P3 |

PRIO    PID     AT      BT      CT      TAT     WT

 3      1       0       8       8       8       0
 4      2       1       2       11      10      8
 4      3       3       4       15      12      8
 5      4       4       1       9       5       4

Avg. TAT = 8.75
Avg. WT = 5.00

*/
