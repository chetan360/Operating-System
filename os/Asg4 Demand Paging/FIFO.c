#include <stdio.h>

int MRU(int time[], int fsize) {
    int max = time[0], pos = 0;
    for(int i=0; i<fsize; i++) {
        if(time[i] > max) {
            max = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int rs[100], frame[20];
    int n, flag1, flag2, pf = 0, hit = 0, rr = 0, fsize;

    printf("Enter no. of pages : ");
    scanf("%d", &n);

    printf("Enter reference string : ");
    for(int i=0; i<n; i++) {
        scanf("%d", &rs[i]);
    } 

    printf("Enter no. of frames :");
    scanf("%d", &fsize);
    for(int i=0; i<fsize; i++) {
        frame[i] = -1;
    }

    for(int i=0; i<n; i++) {
        flag1 = flag2 = 0;
        for(int j=0; j<fsize; j++) {
            if(frame[j] == rs[i]) {
                hit++;
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
                    break;
                }
            }     
        }

        if(flag2 == 0) {
            //MRU finds min timestamp frame pos
            frame[rr] = rs[i];
            rr = (rr+1) % fsize; //circular queue indexing for frame arr
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