#include <stdio.h>

int MRU(int time[], int fsize) {
    int max = time[0], pos = 0;
    for(int i=1; i<fsize; i++) {
        if(time[i] > max) {
            max = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int rs[100], time[20], frame[20];
    int n, flag1, flag2, pf = 0, hit = 0, fsize;

    printf("How many pages : ");
    scanf("%d", &n);

    printf("Enter reference string : ");
    for(int i=0; i<n; i++) {
        scanf("%d", &rs[i]);
    } 

    printf("Enter no. of frames :");
    scanf("%d", &fsize);
    for(int i=0; i<fsize; i++) {
        frame[i] = -1;
        time[i] = 0;
    }

    for(int i=0; i<n; i++) {
        flag1 = flag2 = 0;
        for(int j=0; j<fsize; j++) {
            if(frame[j] == rs[i]) {
                hit++;
                //updating timestamp of frame in time arr
                time[j] = i+1;
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag1 == 0) {
            for(int j=0; j<fsize; j++) {
                //frame is empty
                if(frame[j] == -1) {
                    flag2 = 1;
                    frame[j] = rs[i];
                    pf++;
                    time[j] = i+1;
                    break;
                }
            }     
        }

        if(flag2 == 0) {
            //find most resently used position using max timestamp
            int pos = MRU(time, fsize);
            frame[pos] = rs[i];
            time[pos] = i+1;
            pf++;
        }
        printf("\n");

        for(int j=0; j<fsize; j++) {
            printf("%d\t", frame[j]);    
        }
    }

    printf("\nNo. of page faults = %d\n", pf);
    printf("No. of page hits = %d\n", hit);

    return 0;
}

/*

How many pages : 16
Enter reference string : 12 15 12 18 6 8 11 12 19 12 6 8 12 15 19 8
Enter no. of frames :4

12      -1      -1      -1
12      15      -1      -1
12      15      -1      -1
12      15      18      -1
12      15      18      6
12      15      18      8
12      15      18      11
12      15      18      11
19      15      18      11
12      15      18      11
6       15      18      11
8       15      18      11
12      15      18      11
12      15      18      11
12      19      18      11
12      8       18      11
No. of page faults = 13
No. of page hits = 3

*/
