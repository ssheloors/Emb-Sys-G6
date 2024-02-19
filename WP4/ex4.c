/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 4
 * Exercise 4
 * Submission code: XXXXXX (provided by your TA-s)
 **/

// Include section
#include <stdbool.h>  // For bool type
#include <stdio.h>    // For file functions, printf, scanf
#include <stdlib.h>   // For rand, srand
#include <time.h>     // For time

// Function declarations
int search_number(int number, int tab[], int size);
void bubble_sort(int number, int tab[]);
void swap(int* x, int* y);

int main() {
    srand(time(NULL));  // seed the random number generator
    int test[] = {1, 2, 34, 5, 67, 3, 23, 12, 13, 10};
    int array_size = sizeof(test) / sizeof(test[0]);
    int random_number = rand() % 100;  // generate a random number between 0 and 99

    search_number(random_number, test, array_size);

    printf("The number %d is at position %d in the array.\n", random_number, search_number(random_number, test, array_size));

    bubble_sort(array_size, test);

    printf("The array after sorting is: ");
    for (int i = 0; i < array_size; i++) {
        printf("%d ", test[i]);
    }
    printf("\n");

    return 0;
}

// Function definitions
int search_number(int number, int tab[], int size) {
    for (int i = 0; i < size; i++) {
        if (tab[i] == number) {
            return i;
        }
    }

    return -1;
}

/*
Code inspired by:
https://www.geeksforgeeks.org/bubble-sort/
*/
void bubble_sort(int number, int tab[]) {
    bool swapped;
    for (int i = 0; i < number - 1; i++) {
        swapped = false;
        for (int j = 0; j < number - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                swap(&tab[j], &tab[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false) break;
    }
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}