/*
Set C]
(2) Implement the C Program to create a child process using fork(), Using exec() system call,
child process will execute the program specified in Set A(1) and parent will continue by
printing message “I am parent “.
*/

//Parent Program (parent_program.c)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if(pid == 0) {
        //child process
        char *args[] = {"./child_program", NULL};

        execv(args[0], args);

        printf("Child process is faild to execute.\n");
    } else if(pid > 0) {
        //Parent process 
        wait(NULL); //wait for child to complete
        printf("I am parent\n");
    } else {
        //forking faild
        printf("Forking faild\n");
    }

    return 0;
}