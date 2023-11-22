/*
Set C]
(1) Implement the C program that accepts an integer array. Main function forks child
process. Parent process sorts an integer array and passes the sorted array to child process
through the command line arguments of execve() system call. The child process uses
execve() system call to load new program that uses this sorted array for performing the
binary search to search the particular item in the array.

*/


//Parent program (parent.c)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* const void *a and *b are pointers to anything int, double, float , etc,.
   1)(int*)a typecast to int from void
   2)*(int*)a dereference the casted type
   3)now a is integer
   
   return value of compare function will affect the sorting order :
   1) < 0 a should go before b
   2) = 0 a and b are equal
   3) > 0 a should go before b
*/
   
int compare(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

int main() {
	int arr[] = {5, 2, 9, 1, 5, 6};
	
	pid_t pid = fork();
	
	if(pid == 0) {
		char *args[] = {"./child", NULL}; //executable fil of child.c
		
		//execv(args[0] is path, args is array of char pointers)
		execv(args[0], args);
		
		// this statement will not be executed
		// because execv is execute the new file in current process
		// it replace the old file
		// never returns to old file
		printf("Child process faild to execve.\n");
	} else if(pid > 0) {
		wait(NULL); //block the parent until any of its children has finished 
		printf("Parent process:\n");
		printf("Parent (PID):%d\n", getpid());
		printf("Sorting array..\n");
		
		//qsort(array, n, sizeof single elt in array, compare is two elts)
		qsort(arr, sizeof(arr)/sizeof(arr[0]), sizeof(arr[0]), compare);
		
		printf("Sorted array :\n");
		
		for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++) {
			printf("%d ", arr[i]);
		}
		
		printf("\n");
	} else {
		printf("Forking error.");
	}
	
	return 0;
}