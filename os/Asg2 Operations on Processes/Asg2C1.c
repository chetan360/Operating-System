#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void typeline(char *s, char *fn) {
	int handle, i=0, cnt=0, n;
	char ch;
	
	if((handle = open(fn, O_RDONLY)) == -1) {
		printf("File %s not found\n", fn);
		return;
	}
	
	if(strcmp(s, "a") == 0) {
		while(read(handle, &ch, 1) != 0) {
			printf("%c", ch);
		}
		printf("\n");
		close(handle);
		return;
	}
	
	n = atoi(s);
	if(n > 0) {
		while(read(handle, &ch, 1) != 0) {
			if(ch == '\n') {
				i++;
			}
			
			if(i == n) {
				break;
			}
			printf("%c", ch);
		}
		printf("\n\n");
		
		close(handle);
		return;
	}
	
	if(n < 0) {
		while(read(handle, &ch, 1) != 0) {
			if(ch == '\n') {
				cnt++;
			}
		}
		
		lseek(handle, 0, SEEK_SET);
		
		while(read(handle, &ch, 1) != 0) {
			if(ch == '\n') {
				i++;
			}
			if(i == cnt+n) {
				break;
			}
		}
		
		while(read(handle, &ch, 1) != 0) {
			printf("%c", ch);
		}
		printf("\n");
		close(handle);
		return;		
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
			if(strcmp(t1, "typeline") == 0) {
				typeline(t2, t3);
			} else {
				printf("%s is not valid cmd.\n", t1);
			}
		}
	}
	
	return 0;
}
				

