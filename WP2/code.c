/*
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 2
 * Exercise 4
 * Submission code: XXXXX (provided by your TA-s)
 */

// Include section
#include <stdio.h>  // For printf

// Declare a new type byte that is an unsigned char (exactly 8 bits)
typedef unsigned char byte;

// Function declarations

byte setBit(byte variable, int bitNumber);      // Check the Java doc for the function
int getBit(byte variable, int bitNumber);       // Check the Java doc for the function
void bin2hex(byte binaryNumber);                // Check the Java doc for the function

/**
 * The main method of the program.
 * @param argc the number of arguments the program receives. Always 1 or greater
 * @param argv an array of arguments (string) the program receives. argv[0] is always the executable's location
 * @returns - 0 if the program ends successfully or due to a expected error
 * @returns - a positive integer if an unexpected error occurs
*/
int main(int argc, char* argv[]) {
    // Declare a byte variable to store the binary value of the input. Initializes as 0
    byte output;

    // Check if the engine is on
    if (argv[1][0] == '1') {
        // Set bit 7 (most significant bit)
        output = setBit(output, 7);
    }
    // If the value of engine_on is neither 1 nor 0
    else if(argv[1][0] != 0) {
        // Print error message
        printf("Invalid engine state. Only 0 (off) or 1 (on).");
        // Exit program
        return 0;
    }

    // Check the possible values of gear_pos (argv[2])
    switch(argv[2][0]) {
        // If the value of the gear_pos is 0, there is no need to set the bit as it is already 0.
        // End the switch statement.
        case '0': break;
        // If the gear_pos is 1
        case '1': {
            // Set bit 4, so the trio dedicated to gear_pos is '001' (1 in binary)
            output = setBit(output, 4);
            // End switch case
            break;
        }
        // If the gear_pos is 2
        case '2': {
            // Set bit 5, so the trio dedicated to gear_pos is '010' (2 in binary)
            output = setBit(output, 5);
            // End switch case
            break;
        }
        // If the gear_pos is 3
        case '3': {
            // Set bits 4 & 5, so the trio dedicated to gear_pos is '011' (3 in binary)
            output = setBit(output, 4);     // Set bit 4
            output = setBit(output, 5);     // Set bit 5
            // End switch case
            break;
        }
        // If the gear_pos is 4
        case '4': {
            // Set bit 6, so the trio dedicated to gear_pos is '100' (4 in binary)
            output = setBit(output, 6);
            // End switch case
            break;
        }
        // If the key position is anything else
        default: {
            // Print error message
            printf("Invalid gear position. Only 0 to 4.");
            // Exit program
            return 0;
        }
    }

    // Check the possible values of key_pos (argv[3])
    switch(argv[3][0]) {
        // If the value of the key_pos is 0, there is no need to set the bit as it is already 0.
        // End the switch statement.
        case '0': break;
        // If the key_pos is 1
        case '1': {
            // Set bit 2, so the pair dedicated to key_pos is '01' (1 in binary)
            output = setBit(output, 2);
            // End switch case
            break;
        }
        // If the key_pos is 2
        case '2': {
            // Set bit 3, so the pair dedicated to key_pos is '10' (2 in binary)
            output = setBit(output, 3);
            // End switch case
            break;
        }
        // If the key position is anything else
        default: {
            // Print error message
            printf("Invalid key position. Only 0 to 2.");
            // Exit program
            return 0;
        }
    }

    // Check if the value for the front brake is 1
    if (argv[4][0] == '1') {
        // Set the least significant bit (LSB) (0)
        output = setBit(output, 1);
    }
    // If the value of the front brake is neither 1 nor 0
    else if(argv[4][0] != 0) {
        // Print error message
        printf("Invalid front brake postion. Only 0 or 1.");
        // Exit program
        return 0;
    }

    // Check if the value for the rear brake is 1
    if (argv[5][0] == '1') {
        // Set the least significant bit (LSB) (0)
        output = setBit(output, 0);
    }
    // If the value of the rear brake is neither 1 nor 0
    else if(argv[5][0] != 0) {
        // Print error message
        printf("Invalid rear brake postion. Only 0 or 1.");
        // Exit the program
        return 0;
    }

    // Convert the byte to hexadecimal
    bin2hex(output);

    // Exit program
    return 0;
}

// Function definitions

/**
 * Sets the given bit in a byte to 1. If the bit was already 1, it returns the number.
 * @param variable the binary number
 * @param bitNumber the index of the bit to be set
 * @returns The number (byte) if the bit was already set to 1 or gives the new number with the bit set.
*/
byte setBit(byte variable, int bitNumber) {
    // Return the number if bit is set or the new number with the given bit set
    return variable | (1 << bitNumber);
}

/**
 * Gets a given bit from a binary number.
 * @param variable the binary number
 * @param bitNumber the index of the bit to get
 * @returns The bit (int) requested.
*/
int getBit(byte variable, int bitNumber) {
    // Returns only the bit needed using bit shifting
    return (variable >> bitNumber) & 1;
}

/**
 * A function to convert a binary number to hexadecimal (lowercase). Prints the final result.
 * @param binaryNumber the number (byte) to be converted.
*/
void bin2hex(byte binaryNumber) {
    // Initialize the number to store the decimal representation of the binary number
    int number = 0;
    // Start at base 2^0 = 1 as it reads right to left
    int base = 1;

    // Iterate through the 8 bits of the byte
    for(int i=0; i<8; i++) {
        // If the current bit is 0
        if (getBit(binaryNumber, i) == 0) {
            // Increase the base only
            base *= 2;
        }
        // If the current bit is 1
        else if (getBit(binaryNumber, i) == 1) {
            // Add the power of 2 to the number
            number += 1*base;
            // Increase the base
            base *= 2;
        }
    }
    // Convert the decimal number to hexadecimal and print it
    printf("%x", number);
}