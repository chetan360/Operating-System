/*
Set A]
(2) Write a program that demonstrates the use of nice() system call. After a child process is
started using fork(), assign higher priority to the child using nice() system call.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>

int main() {
	pid_t pid = fork();
	
	if(pid == 0) {
		printf("I am child process :\n");
		printf("Child process id %d\n", getpid());
		printf("Before nice call Priority : %d\n", getpriority(PRIO_PROCESS, getpid()));
		printf("Nice value : %d\n", nice(5));
		printf("After nice call Priority : %d\n", getpriority(PRIO_PROCESS, getpid()));
	} else if(pid > 0) {
		printf("I am parent process :\n");
		printf("parent process id %d\n", getpid());
		printf("Before nice call Priority : %d\n", getpriority(PRIO_PROCESS, getpid()));
		printf("Nice value : %d\n", nice(19));
		printf("After Priority : %d\n", getpriority(PRIO_PROCESS, getpid()));
	} else  {
		printf("forking error");
	}
	
	return 0;
}