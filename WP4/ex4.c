/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 4
 * Exercise 4
 * Submission code: 134256 (provided by your TA-s)
 **/

// Include section
#include <stdbool.h>  // For bool type
#include <stdio.h>    // For file functions, printf, scanf
#include <stdlib.h>   // For rand, srand
#include <time.h>     // For time

// Function declarations

/**
 * A function that searches for a number in an array and return the first position of the number. (linear search)
 *
 * @param number the number to be searched
 * @param tab[] the array in which the number is searched
 * @param size the size of the array
 *
 * @return the position of the number in the array
 **/
int search_number(int number, int tab[], int size);

/**
 * A function that sorts an array of integers in ascending order.
 *
 * @param number the size of the array
 * @param tab[] the array to be sorted
 **/
void sort(int number, int tab[]);

/**
 * A function that swaps two integers.
 *
 * @param x a pointer to the first integer
 * @param y a pointer to the second integer
 **/
void swap(int* x, int* y);

// Main function
int main() {
    srand(time(NULL));                                  // seed the random number generator
    int test[] = {1, 2, 34, 5, 67, 3, 23, 12, 13, 10};  // test array provided in the exercise description
    int array_size = sizeof(test) / sizeof(test[0]);    // calculate the size of the array by dividing the size of the array by the size of the first element (integer)
    int random_number = rand() % 100;                   // generate a random number between 0 and 99

    // Print out the position of the random number in the array by calling the search_number function
    printf("The number %d is at position %d in the array.\n", random_number, search_number(random_number, test, array_size));

    // Sort the array using the sort function and providing the size of the array and the array itself
    sort(array_size, test);

    // Print out the sorted array
    printf("The array after sorting is: ");
    // A for loop to print out the elements of the array
    for (int i = 0; i < array_size; i++) {
        printf("%d ", test[i]);
    }
    printf("\n");  // Print a new line for better readability

    return 0;  // Return 0 to indicate successful execution of the program
}

// Function definitions

int search_number(int number, int tab[], int size) {
    // A for loop to iterate through the array
    for (int i = 0; i < size; i++) {
        // If the number is found, return the position
        if (tab[i] == number) {
            return i;  // Return the position of the number
        }
    }

    return -1;  // If the number is not found, return -1
}

/**
 * Code inspired by:
 * https://www.geeksforgeeks.org/bubble-sort/
 **/
void sort(int number, int tab[]) {
    bool swapped;  // A helper boolean variable to check if the array is sorted

    // A for loop to iterate through the array, number - 1 times as the last element will be sorted by the time the rest of the array is sorted
    for (int i = 0; i < number - 1; i++) {
        swapped = false;  // Set the swapped variable to false at the beginning of each iteration
        for (int j = 0; j < number - i - 1; j++) {
            // If the current element is greater than the next element, swap them and set the swapped variable to true
            if (tab[j] > tab[j + 1]) {
                swap(&tab[j], &tab[j + 1]);  // Call the swap function to swap the elements
                swapped = true;              // Set the swapped variable to true
            }
        }

        // If no two elements were swapped by the inner loop, then break the outer loop as the array is sorted
        if (swapped == false) break;
    }
}

void swap(int* x, int* y) {
    int temp = *x;  // A temporary variable to store the value of the first integer
    *x = *y;        // Set the value of the first integer to the value of the second integer
    *y = temp;      // Set the value of the second integer to the value of the temporary variable
}