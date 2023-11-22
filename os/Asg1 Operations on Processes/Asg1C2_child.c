/*
Set C]
(2) Implement the C Program to create a child process using fork(), Using exec() system call,
child process will execute the program specified in Set A(1) and parent will continue by
printing message “I am parent “.
*/

//Child program (child_program.c)

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("I am child process\n");
    printf("Child Process ID : %d\n", getpid());

    return 0;
}