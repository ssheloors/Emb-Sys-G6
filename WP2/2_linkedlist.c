/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 2
 * Exercise 2
 * Submission code: XXXXXX (provided by your TA-s)
 **/

// Include statements
#include <stdio.h>   // include the standard input/output library for the printf and scanf functions
#include <stdlib.h>  // include the standard library for the malloc and free functions used for dynamic memory allocation
#include <time.h>    // include the time library for the random seed generation function srand and the time function time

// #### Constants #####
#define MAX 5

// ##### typedefs ####
// define a structure for the nodes of the linked list with a number as a value, a pointer to the next and previous nodes
typedef struct q {
    int number;
    struct q* next;
    struct q* prev;
} REGTYPE;

// ##### Function declarations #####
/**
 * This function creates a linked list with MAX elements, each element of the list will store a random value from 0 to a 100 and
 * will have a pointer to the previous and next node.
 *
 * @param void
 * @return REGTYPE* - a pointer to the head node of the linked list
 **/
REGTYPE* random_list(void);

/**
 * This function adds a new node to the linked list and sets the new node as the head node.
 *
 * @param temp a pointer to the head node of a linked list
 * @param data the value of the node to be stored in the new head node
 * @return REGTYPE* - a pointer to the new head node of the linked list
 **/
REGTYPE* add_first(REGTYPE* temp, int data);

// ###### Main program #######
int main() {
    int nr = 0;                       // declare number to be used to print the list item number
    REGTYPE *act_post, *head = NULL;  // declare the post and the head nodes
    srand(time(0));                   // Random seed
    head = random_list();             // call random list function on head
    act_post = head;                  // set the current post to be the head

    while (act_post != NULL) {                                 // while the current post is not null
        printf("\n Post nr %d : %d", nr++, act_post->number);  // print the value of the post and increment the item number every time
        act_post = act_post->next;                             // set the current post to be the next item in the linked list
    }

    int input;                                                     // declare input variable to store user input for the new head value
    printf("\n Enter new head value - ");                          // ask the user to enter a new head value
    scanf("%d", &input);                                           // read the user input and save it in the input variable
    REGTYPE* newList = add_first(head, input);                     // call the add_first function to add a new head to the linked list
    nr = 0;                                                        // reset the item number to 0
    while (newList != NULL) {                                      // while the new list is not null
        printf("\n List item nr %d : %d", nr++, newList->number);  // print the value of the list item and increment the item number every time
        newList = newList->next;                                   // set the new list to be the next item in the linked list
    }

    // --- Free the allocated memory ---
    while ((act_post = head) != NULL) {  // while the current post is not null
        head = act_post->next;           // set the head to the next element
        free(act_post);                  // free up the memory used by the post
    }

    return 0;
}

// ==== End of main ======================================

// ##### Function implementations #####
REGTYPE* random_list(void) {
    REGTYPE *top, *old, *item;                // initialize variables for saving the nodes
    top = (REGTYPE*)malloc(sizeof(REGTYPE));  // allocate memory for the head node (top)
    top->number = rand() % 101;               // assign a random value to the head node from 0 to 100
    top->next = NULL;                         // next node for head node is null
    top->prev = NULL;                         // previous node for head node is null
    old = top;                                // set the previous node to be the current for later usage

    // loop through the list and add nodes to the linked list until the MAX value (5) is reached
    for (int j = 2; j <= MAX; j++) {
        item = (REGTYPE*)malloc(sizeof(REGTYPE));  // allocate memory for the new node
        item->number = rand() % 101;               // assign a random value to the new node from 0 to 100
        old->next = item;                          // point the previous node to the current one
        item->prev = old;                          // point the current node to the previous one saved in old before
        old = item;                                // set the previous node to be the current for later usage
    }

    old->next = NULL;  // set the next node for the last node to be null

    return (top);  // return the head node
}

REGTYPE* add_first(REGTYPE* temp, int data) {
    REGTYPE* new;                             // create a new node for the list
    new = (REGTYPE*)malloc(sizeof(REGTYPE));  // allocate the memory for the node
    temp->prev = new;                         // set the previous item of the given node to be the new item
    new->number = data;                       // set the number of the node to be the inputted data
    new->next = temp;                         // set the inputted node to be the next of the new node
    new->prev = NULL;                         // set the previous node of the new one as null, this means that new is now the head

    return (new);  // return the new head
}
