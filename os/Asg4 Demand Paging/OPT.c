#include <stdio.h>

int main() {
    int rs[100], frame[20], future[10];
    int n, flag1, flag2, flag3, pf = 0, hit = 0, fsize, pos, max;

    printf("Enter no. of pages : ");
    scanf("%d", &n);

    printf("Enter reference string : ");
    for(int i=0; i<n; ++i) {
        scanf("%d", &rs[i]);
    } 

    printf("Enter no. of frames :");
    scanf("%d", &fsize);
    for(int i=0; i<fsize; ++i) {
        frame[i] = -1;
    }

    for(int i=0; i<n; ++i) {
        flag1 = flag2 = 0;
        for(int j=0; j<fsize; j++) {
            if(frame[j] == rs[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag1 == 0) {
            for(int j=0; j<fsize; ++j) {
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
            flag3 = 0;
            for(int j=0; j<fsize; ++j) {
                future[j] = -1;
                for(int k=i+1; k<n; ++k) {
                    if(frame[j] == rs[k]) {
                        hit++;
                        future[j] = k;
                        break;
                    }
                }
            }

            for(int j=0; j<fsize; ++j) {
                if(future[j] == -1) {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            if(flag3 == 0) {
                max = future[0];
                pos = 0;

                for(int j=1; j<fsize; ++j) {
                    if(future[j] > max) {
                        max = future[j];
                        pos = j;
                    }
                }
            }

            frame[pos] = rs[i];
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