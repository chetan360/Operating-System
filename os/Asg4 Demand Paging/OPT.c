#include <stdio.h>

int OPT(int future[], int fsize) {
	int maxFuture=future[0], pos=0;
	for(int i=1; i<fsize; i++) {
		if(future[i] > maxFuture) {
			maxFuture = future[i];
			pos = i;		
		}
	}
	
	return pos;
}

int main() {
	int rs[100], frame[20], future[20];
	int n, fsize, flag1, flag2, flag3, pos, pf=0, hit=0;
	
	printf("How many pages : ");
	scanf("%d", &n);
	
	printf("Enter reference string : ");
	for(int i=0; i<n; i++) {
		scanf("%d", &rs[i]);
	}
	
	printf("How many pages : ");
	scanf("%d", &fsize);
	for(int i=0; i<fsize; i++) {
		frame[i] = -1;
	}
	
	for(int i=0; i<n; i++) {
		flag1 = flag2 = 0;
		for(int j=0; j<fsize; j++) {
			//page is allready in the frames
			if(frame[j] == rs[i]) {
				flag1 = flag2 = 1;
				hit++;
				break;
			}
		}
		
		if(flag1 == 0) {
			for(int j=0; j<fsize; j++) {
				//frame is empty 
				if(frame[j] == -1) {
					flag2 = 1;
					pf++;
					frame[j] = rs[i];
					break;
				}
			}
		}
		
		if(flag2 == 0) {
			flag3 = 0;
			//check page is demanded in future
			for(int j=0; j<fsize; j++) {
				future[j] = -1;
				for(int k=i+1; k<n; k++) {
					if(frame[j] == rs[k]) {
						//record that pos in future arr
						future[j] = k;
						break;
					}
				}
			}
			
			//if page is not demanded in future
			for(int j=0; j<fsize; j++) {
				if(future[j] == -1) {
					//then replace that page
					pos = j;
					flag3 = 1;
					break;
				}
			}
			
			if(flag3 == 0) {
				//opt returns page which is demanded last having max pos in future arr
				pos = OPT(future, fsize);
			}
			frame[pos] = rs[i];
			pf++;
		}
		printf("\n");
		for(int j=0; j<fsize; j++) {
			printf("%d\t", frame[j]);
		}
	}
	
	printf("\n\nno. of page faults = %d\n", pf);
	printf("no. of hits = %d\n", hit);
	
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
