/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 3
 * Exercise 6
 * Submission code: XXXXXX (provided by your TA-s)
 **/

// Include section
#include <stdio.h>   // For printf, scanf
#include <string.h>  // For strcpy

// Define section
#define MAX 21  // define the maximum size of the character input, 20 characters + 1 for the null-terminator

// Function declarations
/**
 * This function copies a string from a given source to a given destination.
 *
 * @param source the string to be copied
 * @param destination the string to copy to
 *
 * @return void
 **/
void copyString(char *source, char *destination);

// Main function
int main() {
    char input[MAX];      // variable to store the user input
    char inputCopy[MAX];  // variable to store the copied string

    printf("Please enter a string: ");

    fgets(input, MAX, stdin);  // read the user input and store it in the input variable

    // copy the input string using the strcpy function, as specified in the exercise
    strcpy(inputCopy, input);

    printf("\n");                                                  // print a newline for better readability
    printf("The copied string using strcpy is: %s\n", inputCopy);  // print the string the user entered

    // copy the input string using a custom function
    copyString(input, inputCopy);

    printf("The copied string using a custom function is: %s\n", input);  // print the string the user entered

    return 0;  // return 0 to indicate the program has run successfully
}

// Function definitions
// check java doc for the function description
void copyString(char *source, char *destination) {
    // loop through the source string and copy each character to the destination string
    for (int i = 0; source[i] != '\0'; i++) {
        destination[i] = source[i];  // copy each character from the source to the destination
        destination[i + 1] = '\0';   // null-terminate the destination string
    }
}