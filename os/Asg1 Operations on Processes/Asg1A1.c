/*Set A]
(1) Implement the C Program to create a child process using fork(), display parent and child
process id. Child process will display the message “I am Child Process” and the parent
process should display “I am Parent Process”.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	pid_t pid = fork(); // creates the exact copy of parent process named as child process
	
	if(pid == 0) {
		printf("I am child process :\n");
		printf("Child process id %d\n", getpid());
	} else if(pid > 0) {
		printf("I am parent process :\n");
		printf("parent process id %d\n", getpid());
	} else  {
		printf("forking error");
	}
	
	return 0;
}