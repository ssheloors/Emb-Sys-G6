/*
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 2
 * Exercise 4
 * Submission code: XXXXX (provided by your TA-s)
 */

// Include section
#include <stdio.h>  // For printf
#include <string.h> // For strcat

// Declare a new type byte that is an unsigned char (exactly 8 bits)
typedef unsigned char byte;

// Create an array to store all binary equivalents of hex values
const char* hexValues[16] = {
    // 0, 1, 2, 3, 4 ..... F
    "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
};

// Function declarations

void hex2bin(char* string, char* output);               // Check the Java doc for the function
int bin2dec(char* string, int low, int high);           // Check the Java doc for the function
void updateTable(int values[], char* binaryString);     // Check the Java doc for the function
void printTable(int values[]);                          // Check the Java doc for the function
int isHexadecimal(char* string);                        // Check the Java doc for the function

/**
 * The main method of the program.
 * @param argc the number of arguments the program receives. Always 1 or greater
 * @param argv an array of arguments (string) the program receives. argv[0] is always the executable's location
 * @returns - 0 if the program ends successfully or due to a expected error
 * @returns - a positive integer if an unexpected error occurs
*/
int main(int argc, char* argv[]) {
    // Check if there is an invalid number of arguments
    if (argc != 2) {
        // Print error message
        printf("Invalid number of arguments.\nFormat: <executable_file> <hexadecimal_string>");
        // Exit program
        return 0;
    }

    if (!isHexadecimal(argv[1])) {
        // Print error message
        printf("Invalid type of value. If you are using uppercase letters, try lowercase instead.");
        // Exit program
        return 0;
    }

    // Declare an array to store the decoded values of the needed variables. Size 5 -> engine_on, gear_pos, key_pos, brake1, brake2
    int values[5];
    // Declare the string to store the binary representation. Size 9 -> 8 bits and 1 null character
    char binaryString[9];

    // Convert the hexedecimal argument to a string of binary
    hex2bin(argv[1], binaryString);

    // Update the table with the decoded values using the string of binary
    updateTable(values, binaryString);

    // Print the table with the decoded values
    printTable(values);
}

// Function definitions

/**
 * Converts a hexadecimal number (string) into binary (string)
 * @param string variable that holds hexidecimal number
 * @param output a pointer to a string that holds the binary representation
*/
void hex2bin(char* string, char* output) {
    // Iterate through all the characters in the string until the null character is encountered
    for(int i=0; string[i] != '\0'; i++) {
        // If the character is a digit (0-9)
        if (string[i] >= '0' && string[i] <= '9') {
            // Change index value from ASCII to its integer form
            // 48 is the difference for digit ASCII and their index in hexValues
            int index = string[i] - 48;
            // Concatenate the binary equivalent to the output variable
            strcat(output, hexValues[index]);
        }
        // If the character is from a to f (lowercase since that's how we get it from code.c) = equivalent to 10-15
        else if (string[i] >= 'a' && string[i] <= 'f') {
            // Change index value from ASCII to 10, 11 etc
            // 87 is the difference for lowercase letter ASCII and their index in hexValues
            int index = string[i] - 87;
            // Concatenate the binary equivalent to the output variable
            strcat(output, hexValues[index]);
        }
    }
}

/**
 * Converts a portion of a binary number (string) into decimal notation
 * @param string the string that contains the binary number
 * @param low the lowest bit to include in the conversion
 * @param high the highest bit to include in the conversion
 * @returns The decimal notation of the number
*/
int bin2dec(char* string, int low, int high) {
    // Initialize the number to store the decimal representation of the binary number
    int number = 0;
    // Start at base 2^0 = 1 as it reads right to left
    int base = 1;
    
    // Iterate through the given range of bits (left to right)
    for(int i=high; i>=low; i--) {
        // If the current bit is 0
        if (string[i] == '0') {
            // Increase the base only
            base *= 2;
        }
        // If the current bit is 1
        else if (string[i] == '1') {
            // Add the power of 2 to the number
            number += 1*base;
            // Increase the base
            base *= 2;
        }
    }

    // Return the number in decimal form
    return number;
}

/**
 * Updates an array of values [engine_on, gear_pos, key_pos, brakes1, brakes2] with the decoded values from a string of binary.
 * @param values the array to be updated
 * @param binaryString the string containing the binary to be decoded
*/
void updateTable(int values[], char* binaryString) {
    // Initialize in (index) as 0
    int i = 0;
    // Iterate through the binary string until the null character is found
    while (binaryString[i] != '\0') {
        // Check the bits of the binary string from right to left
        switch(i) {
            // If it's bit 0
            case 0: {
                // Update the value of engine_on to 1 or 0 depending on the value of bit 0
                values[0] = (binaryString[i] == '1') ? 1 : 0;
                // End switch statement
                break;
            }
            // If it's bit 1, it reads bits 1 to 3
            case 1: {
                // Update the value of gear_pos depending on the value of bits 1 to 3
                values[1] = bin2dec(binaryString, 1, 3);
                // End switch statement
                break;
            }
            // If it's bit 4, it reads bits 4 to 5
            case 4: {
                // Update the value of key_pos depending on the value of bits 4 to 5
                values[2] = bin2dec(binaryString, 4, 5);
                // End switch statement
                break;
            }
            // If it's bit 6
            case 6: {
                // Update the value of brakes1 to 1 or 0 depending on the value of bit 6
                values[3] = (binaryString[i] == '1') ? 1 : 0;
                // End switch statement
                break;
            }
            // If it's bit 7
            case 7: {
                // Update the value of brakes2 to 1 or 0 depending on the value of bit 7
                values[4] = (binaryString[i] == '1') ? 1 : 0;
                // End switch statement
                break;
            }
            // If any other value, break
            default: break;
        }

        // Increase the value of i
        i++;
    }
}

/**
 * Print a table of values according to the format described in the assignment description
 * @param values the array that stores the values (int) needed to be printed
*/
void printTable(int values[]) {
    // Print column names
    printf("Name \t\t Value\n");
    // Print separator
    printf("-----------------------------\n");
    // Print engine_on row
    printf("engine_on\t %d\n", values[0]);
    // Print gear_pos row
    printf("gear_pos\t %d\n", values[1]);
    // Print key_pos row
    printf("key_pos\t\t %d\n", values[2]);
    // Print brake1 row
    printf("brake1\t\t %d\n", values[3]);
    // Print brake2 row
    printf("brake2\t\t %d\n", values[4]);
}

int isHexadecimal(char* string) {
    // Iterate through all the characters in the string until the null character is encountered
    for (int i=0; string[i] != '\0'; i++) {
        // If the character is not a digit nor a lowercase letter
        if ((string[i] < '0' || string[i] > '9') && (string[i] < 'a' || string[i] > 'f')) {
            // Return false
            return 0;
        }
    }
    // Else, return true
    return 1;
}