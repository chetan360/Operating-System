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

	//open the file 
	if((handle = open(fn, O_RDONLY)) == -1) {
		printf("File %s not found\n", fn);
		return;
	}
	
	if(strcmp(s, "a") == 0) {
		//printing till end of file is not occurred 
		while(read(handle, &ch, 1) != 0) {
			printf("%c", ch);
		}
		printf("\n");
		//close file
		close(handle);
		return;
	}
	
	n = atoi(s);
	if(n > 0) {
		//1. print from frist line and count
		//   no. of lines in i
		while(read(handle, &ch, 1) != 0) {
			if(ch == '\n') {
				i++;
			}
			//2. i becomes n the stop printing
			if(i == n) {
				break;
			}
			printf("%c", ch);
		}
		printf("\n\n");

		//close file
		close(handle);
		return;
	}
	
	if(n < 0) {
		//1. count no. of lines
		while(read(handle, &ch, 1) != 0) {
			if(ch == '\n') {
				cnt++;
			}
		}

		//file read location is reached to end line
		//so seek at first line
		lseek(handle, 0, SEEK_SET);

		//2. seeking file read location to 
		//   no. of lines + (-n) 
		while(read(handle, &ch, 1) != 0) {
			if(ch == '\n') {
				i++;
			}
			if(i == cnt+n) {
				break;
			}
		}

		//3. printing from that last -n lines
		while(read(handle, &ch, 1) != 0) {
			printf("%c", ch);
		}
		printf("\n");

		//close file
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
		} else {
			printf("please enter (typeline n/-n/a filename) cmd in this format.\n");
		}
	}
	
	return 0;
}
				

