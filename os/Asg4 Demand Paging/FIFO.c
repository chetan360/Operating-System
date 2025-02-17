#include <stdio.h>

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
            //inserting page in frames in sequential manner
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

/*

How many pages : 16
Enter reference string : 12 15 12 18 6 8 11 12 19 12 6 8 12 15 19 8
How many pages : 4

12      -1      -1      -1
12      15      -1      -1
12      15      -1      -1
12      15      18      -1
12      15      18      6
12      15      8       6
12      11      8       6
12      11      8       6
12      19      8       6
12      19      8       6
12      19      8       6
12      19      8       6
12      19      8       6
15      19      8       6
15      19      8       6
15      19      8       6

no. of page faults = 8
no. of hits = 8

*/
