/*
Set B]
(2) Write a C program to illustrate the concept of orphan process. Parent process creates a
child and terminates before child has finished its task. So child process becomes orphan
process. (Use fork(), sleep(), getpid(), getppid()).
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	pid_t pid = fork();
	
	if(pid == 0) {
		printf("Child process :\n");
		sleep(5);
		printf("I am child and I am orphan now\n");
	} else if(pid > 0) {
		printf("Parent process :\n");
		printf("Parent (PID) : %d\n", getpid());
		printf("Child (PID) : %d\n", pid);
		printf("Parent is terminnating\n");
	} else {
		printf("Forking error");
	}
	
	return 0;
}