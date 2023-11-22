/*
Set C]
(1) Implement the C program that accepts an integer array. Main function forks child
process. Parent process sorts an integer array and passes the sorted array to child process
through the command line arguments of execve() system call. The child process uses
execve() system call to load new program that uses this sorted array for performing the
binary search to search the particular item in the array.
*/

//Child program (child.c)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int binarySearch(int arr[], int left, int right, int target) {
    while(left <= right) {
        int mid = (right + left) / 2;

        if(arr[mid] == target) {
            return mid;
        } else if(target < arr[mid]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    //target not found
    return -1;
}

int main() {
    // binary search needs sorted array
    int sortedArray[] = {1, 2, 5, 5, 6, 9};

    printf("Child process :\n");
    printf("Child PID : %d\n", getpid());

    int target = 5;
    // no. of elt in array = sixeof(sortedArray)/sizeof(sortedArray[0])
    int i = binarySearch(sortedArray, 0, sixeof(sortedArray)/sizeof(sortedArray[0])-1, target); 

    if(i != -1) {
        printf("Item %d is fount at index %d\n", target, i);
    } else {
        printf("Item %d not fount in the array.\n", target);
    }

    return 0;
}