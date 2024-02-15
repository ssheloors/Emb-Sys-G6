/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 3
 * Exercise 5
 * Submission code: XXXXXX (provided by your TA-s)
 **/

// Include section
#include <stdio.h>   // For file functions, printf, scanf
#include <stdlib.h>  // For rand, srand
#include <time.h>    // For time

// Define section
#define MAX 10  // define the maximum size of the array, for example 10

// Main function
int main() {
    int array[MAX];  // declare an array of integers and allocate memory for MAX amount of elements

    srand(time(NULL));               // seed the random number generator
    for (int i = 0; i < MAX; i++) {  // go through each element in the array
        array[i] = rand() % 99 + 1;  // fill it with random numbers between 1 and 99
    }

    // print the value of the address of the array using a pointer with the %p format specifier
    printf("The value of the address of the array (pointer) is: %p\n", array);

    // print the value of the first integer in the array using a pointer to the first element in the array with the %d format specifier
    printf("First integer in the array is (array[0]): %d\n", *array);

    // print the value of the last integer in the array by using MAX-1 to get the last element with the %d format specifier
    printf("The last integer in the array is: %d\n", array[MAX - 1]);

    // print the size of an integer (number of bytes) using the sizeof operator with the %lu (unsigned long) format specifier
    printf("The size of an integer (number of bytes) is: %lu\n", sizeof(int));

    // print the size of the whole array in bytes using the sizeof operator with the %lu (unsigned long) format specifier
    printf("The size of the whole array in bytes is: %lu\n", sizeof(array));

    // create a pointer to the first element in the array
    int *pArray = array;

    // go through the array and print the value of each element and the value doubled
    for (int i = 0; i < MAX; i++) {
        // print the value of every element and its value doubled
        printf("Value: %d, Doubled: %d\n", *pArray, array[i] * 2);
        // move the pointer to the next element in the array
        pArray++;
    }

    return 0;  // return 0 to indicate the program has run successfully
}