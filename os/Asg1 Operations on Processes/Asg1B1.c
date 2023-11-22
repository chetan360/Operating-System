/*
Set B]
(1) Implement the C program to accept n integers to be sorted. Main function creates child
process using fork system call. Parent process sorts the integers using bubble sort and
waits for child process using wait system call. Child process sorts the integers using
insertion sort.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        for(int j=0; j<n-i; j++) {
            //Swap arr[j] and arr[j+1]
            if(arr[j] > arr[j+1]) {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for(int i=1; i<n; i++) {
        int curr = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > curr) {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = curr;
    }
}

int main() {
    int n;
    printf("How many values : ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d values :\n", n);
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if(pid == 0) {
        //Child process
        printf("Child process sorting using insertion sort..\n");

        insertionSort(arr, n);

        printf("Child process sorted array :\n");
        for(int i=0; i<n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else if(pid > 0) {
        //Parent process
        wait(NULL);
        printf("Parent process sorting using bubble sort..\n");

        bubbleSort(arr, n);

        printf("Parent process sorted array :\n");
        printf("Child process sorted array :\n");
        for(int i=0; i<n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        // Forking error
        printf("Forking error");
    }

    return 0;
}