#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void count(char c, char *fname) {
	int lc=0, wc=0, cc=0, handle;
	char ch;
	
	if((handle = open(fname, O_RDONLY)) == -1) {
		printf("File %s not found\n", fname);
		return;
	}
	
	while(read(handle, &ch, 1) != 0) {
		if(ch == ' ') {
			wc++;
		} else if(ch == '\n') {
			lc++;
			wc++;
		} else {
			cc++;
		}
	}
	
	close(handle);
	
	switch(c) {
		case 'c':
			printf("Total no. of Characters = %d\n", cc);
			break;
		case 'w':
			printf("Total no. of Words = %d\n", wc);
			break;
		case 'l':
			printf("Total no. of Lines = %d\n", lc);
			break;
	}
}

int main() {
	char command[80], t1[20], t2[20], t3[20];
	int n;
	
	system("clear");
	
	while(1) {
		printf("myShell$ : ");
		fflush(stdin);
		
		fgets(command, 80, stdin);
		n = sscanf(command, "%s %s %s", t1, t2, t3);
		
		if(n == 3) {
			if(strcmp(t1, "count") == 0) {
				count(t2[0], t3);
			} else {
				printf("%s is not valid cmd.\n", t1);
			}
		}
	}
	
	return 0;
}
				

