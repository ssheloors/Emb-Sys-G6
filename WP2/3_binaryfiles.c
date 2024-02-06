/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 2
 * Exercise 3
 * Submission code: 665721 (provided by your TA-s)
 **/

// Include section
#include <stdlib.h>     // From template
#include <stdio.h>      // For file functions, printf, scanf
#include <string.h>     // For strcmp, strcpy
#include <stdbool.h>    // For booleans
// -----typedefs -------
typedef struct
{
    char firstname[20]; //first name
    char lastname[20]; //last name
    char pers_number[13]; // yyyymmddnnnc
} PERSON;

PERSON input_record(void);             // Reads a person’s record.

/**
 * Creates a file and writes the first record
 * @param inrecord
 * **/ 
void write_new_file(PERSON *inrecord);  

/**
 * Searches for a person with the provided string as first or last name
 * @param name
*/
void search_by_firstname(char *name); 

/**
 * Prints the full content of the file skipping the first dummy data 
*/

void printfile(void); // Prints out all persons in the file
/**
 * appends a new person to the file
 * @param inrecord
*/
void append_file(PERSON *inrecord); 

/**
 * Function to prompt the user to input data to create a new person
 * @return PERSON
*/
PERSON createPerson();

int main(void)
{
    // A variable for a person
    PERSON ppost;
    // A variable for storing the menu option selected by the user
    int option;

    // Continue loop as long as user does not input the exit code (5 in this case)
    while(option != 5){
        //print the menu to the user
        printf("1 Create a new and delete the old file \n");
        printf("2 Add a new person to the file \n");
        printf("3 Search for a person in the file \n");
        printf("4 Print out all in the file \n");
        printf("5 Exit the program \n");
        scanf("%d", &option); //read the user input
        
        switch (option) // check the input of the user 
        {
        case 1: //create a new file with dummy data
            write_new_file(&ppost); //call the function to create a new file
            break;  // end switch
        case 2: //add a new person to the file
            PERSON newPerson = createPerson(); //create a new person by calling a method that will prompt the user for data
            append_file(&newPerson); //add the created person to the file
            break;  // end switch
        case 3: //search in the file
            char name[30]; //name to be found

            printf("Enter a name to be found - ");
            scanf("%s", &name); //scan the input
            search_by_firstname(name); //call the search function with the inputted value
            break;  // end switch
        case 4: // print the entire file
            printfile();    // print the entire file
            break; // end switch
        default:    // any other value
            break; // end switch
        }

    }

    // exit program
    return (0);
}

void write_new_file(PERSON *inrecord){
    FILE *file; //declare a file pointer

    file = fopen("binaryfile.bin", "wb"); //create and open the file, name it and set it to write binary
    if(file==NULL){ //if the file is null after creation, return an error
        printf("Unable to create a new file \n");
        // Return nothing
        return;
    }

    fwrite(inrecord, sizeof(PERSON), 1, file); //write inrecord into the file 
    fclose(file);     //close file 
}

void append_file(PERSON *inrecord){
    FILE *file; //declare a file pointer 
    file = fopen("binaryfile.bin", "ab"); //open the file with that name in append binary mode
    if(file == NULL){ //if the file is null, prompt an error
        printf("Unable to open file, check if the file exists \n");
        // Return nothing
        return;
    }
    fwrite(inrecord, sizeof(PERSON), 1, file); //write the record to the file
    fclose(file); //close the file
}

PERSON createPerson(){
    char inputFirstname[20]; //variable for the input of firstname
    char inputLastname[20]; //variable for the input of last name
    char inputPers_number[13]; //variable for the input of personnumer

    //Prompt the user to input data to create a person
    printf("Create a new person \n");
    printf("Enter a first name - ");
    scanf("%s", inputFirstname); //save the fisrt name

    printf("Enter last name - ");
    scanf("%s", inputLastname); //save the last name

    printf("Enter personnumer - ");
    scanf("%s", inputPers_number); //save the personnumer

    PERSON newPerson; //create a new person 
    strcpy(newPerson.firstname, inputFirstname); //copy the value of the name input to the name field of person 
    strcpy(newPerson.lastname, inputLastname); //copy the value of the last name input to the last name field of person 
    strcpy(newPerson.pers_number, inputPers_number); //copy the value of the personnumer name input to the personnumer field of person 

    return(newPerson); //return the created person
}

void search_by_firstname(char *name){
    PERSON person; //declare a person that will later be used to look into the file
    bool found = false; //boolean to know if we have found a match

    FILE *file = fopen("binaryfile.bin", "rb"); //open file in read binary mode
    if(file == NULL){ //if the file was not open prompt an error
        printf("Unable to open the file.\n");
        // Return nothing
        return;
    }

    //check if the file is empty
    fseek(file, 0, SEEK_END); //move the position in the file to the end 
    if(ftell(file) == 0){ //use ftell to check your position in the file, if it is 0 you are still at the start meaning it is empty
        printf("The file is empty \n");
        fclose(file); //close the file
        // return nothing
        return;
    }
    rewind(file); //reset the position in the file 

    //loop while the scanner can read a person in the file
    while(fread(&person, sizeof(PERSON), 1, file) == 1){  //fread returns 1 if it was able to read a person in the file
        if(strcmp(person.firstname, name) == 0 ||strcmp(person.lastname, name) == 0){ // compare the string that we want to find with what was found in the append_file
            printf("Person found: %s %s \n", person.firstname, person.lastname); //print data of the 
            found = true; //if you found a person change the booolean to true
        }
    }

    if(!found){ //if the boolean is still false after the loop, no person was found
        printf("The file does not contain matches to your input \n");
    }

    fclose(file); //close the file at the end of the function

}

void printfile(void){
    PERSON person; //declare a person 
    int counter = 1; //start counter in 1 to index when printing

    FILE *file = fopen("binaryfile.bin", "rb"); //open file in binary read mode 

    //check if the file is empty
    fseek(file, 0, SEEK_END); //move the position in the file to the end 
    if(ftell(file) == 0){ //use ftell to check your position in the file, if it is 0 you are still at the start meaning it is empty
        printf("The file is empty \n");
        fclose(file); //close the file
        // return nothing
        return;
    }
    rewind(file); //reset the position in the file 

    fseek(file, 53, SEEK_SET); //move the file pointer 53 bits to skip the first data elemnt (always dummy when file is created)
    while(fread(&person, sizeof(PERSON), 1, file) == 1){  //fread returns 1 if it was able to read a person in the file
        printf("Person %d: Full Name: %s %s SSN: %s \n", counter++, person.firstname, person.lastname, person.pers_number);
    }
    
}