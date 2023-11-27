#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void typeline(char *s, char *filename) {
	int fp, i=0, n;
	char ch;
	
	//open the file
	if((fp = open(filename, O_RDONLY)) == -1) {
		printf("File %s not found\n", filename);
		return;
	}
	
	if(strcmp(s, "-a") == 0) {
		while(read(fp, &ch, 1) != 0) {
			printf("%c", ch);
		}
		printf("\n\n");
		//close file
		close(fp);
		return;
	}
	
	n = atoi(s); 
	if(n > 0) {
		//print from first line and count
		//no. of lines in i
		while(read(fp, &ch, 1) != 0) {
			if(ch == '\n') {
				i++;
			}
			if(i == n) {
				break;
			}
			printf("%c", ch);
		}
		printf("\n\n");
		
		//close file
		close(fp);
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
				printf("%s is invalid command.\n", t1);
			}
		} else {
			printf("please enter (typeline +n/-a filename) command in this form.\n ");
		}
	}

	return 0;
}

