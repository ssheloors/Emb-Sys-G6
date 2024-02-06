/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 2
 * Exercise 1
 * Submission code: 665721 (provided by your TA-s)
 **/

// Include statements
#include <stdio.h> // include the standard input/output library for the printf and scanf functions

// create an enum for the directions (North, East, South, West)
enum DIRECTION { N,
                 E,
                 S,
                 W };

// create a structure for the robot with x and y position and the direction it is facing
typedef struct {
    // The position based on the x-axis
    int xpos;
    // The position based on the y-axis
    int ypos;
    // The direction it is facing
    enum DIRECTION dir;
} ROBOT;

// Function declarations
/**
 * This function moves the robot one step in the direction it is facing
 * @param robot a pointer to the robot structure
 * @return void
 **/
void move(ROBOT* robot);

/**
 * This function turns the robot 90 degrees to the right
 * @param robot a pointer to the robot structure
 * @return void
 */
void turn(ROBOT* robot);

/**
 * This function returns the name of the direction based on the enum
 * @param DIR the direction
 * @return const char* the name of the direction
 */
const char* getDirName(enum DIRECTION DIR);

int main() {
    // variable declarations
    ROBOT robot;      // create a robot structure
    char input[100];  // create a variable to store the user input for the movement sequence
    int repeat = 1;   // if the user wants to repeat the program or not

    // repeat the program until the user wants to exit
    while (repeat) {
        printf("Provide starting x position (0-99):\n");
        if (scanf("%d", &robot.xpos) != 1) {  // check if the input is a number
            printf("Error, please enter a valid number.\n");
            // Exit program
            return 0;
        }
        if (robot.xpos < 0 || robot.xpos > 99) {  // check if the input is between 0 and 99
            printf("Error, please enter a number between 0 and 99.\n");
            // Exit program
            return 0;
        }

        printf("Provide starting y position (0-99):\n");
        if (scanf("%d", &robot.ypos) != 1) {  // check if the input is a number
            printf("Error, please enter a valid number.\n");
            // Exit program
            return 0;
        }
        if (robot.ypos < 0 || robot.ypos > 99) {  // check if the input is between 0 and 99
            printf("Error, please enter a number between 0 and 99.\n");
            // Exit program
            return 0;
        }

        robot.dir = N;  // set the starting direction to North

        printf("Provide movement sequence, the starting direction is North (m for move, t for turn, e for exit):\n");
        scanf("%s", input);  // read the user input for the movement sequence

        // loop through the input and move the robot based on the input
        for (int i = 0; input[i] != '\0'; i++) {
            // Go through possible values of the input
            switch (input[i]) {
                // if the input is 'm', move the robot
                case 'm':
                    // Move the robot
                    move(&robot);
                    // End switch
                    break;
                // if the input is 't', turn the robot
                case 't':
                    // Turn the robot
                    turn(&robot);
                    // End switch
                    break;
                // if the input is 'e', exit the program
                case 'e':
                    repeat = 0;  // set repeat to 0 to break the loop and exit the program
                    // End switch
                    break;
                // if the input is not valid, print an error message
                default:
                    printf("Invalid input.\n");
                    // End switch
                    break;
            }

            if (repeat == 0) {  // if the user wants to exit the program, break the loop
                break;
            }
        }

        // print the robot position and direction after the movement sequence
        printf("Robot position: (%d, %d), direction: %s\n", robot.xpos, robot.ypos, getDirName(robot.dir));
    }
    return 0;  // return 0 to end the program
}

// Function implementations
void move(ROBOT* robot) {
    // move the robot based on the direction it is facing
    switch (robot->dir) {
        // if the direction is North, increment the y position
        case N:
            robot->ypos++;
            // End switch
            break;
        // if the direction is East, increment the x position
        case E:
            robot->xpos++;
            // End switch
            break;
        // if the direction is South, decrement the y position
        case S:
            robot->ypos--;
            // End switch
            break;
        // if the direction is West, decrement the x position
        case W:
            robot->xpos--;
            // End switch
            break;
    }
}

void turn(ROBOT* robot) {
    // turn the robot 90 degrees to the right based on the direction it is facing
    switch (robot->dir) {
        // if the direction is North, set the direction to East
        case N:
            robot->dir = E;
            // End switch
            break;
        // if the direction is East, set the direction to South
        case E:
            robot->dir = S;
            // End switch
            break;
        // if the direction is South, set the direction to West
        case S:
            robot->dir = W;
            // End switch
            break;
        // if the direction is West, set the direction to North
        case W:
            robot->dir = N;
            // End switch
            break;
    }
}

const char* getDirName(enum DIRECTION DIR) {
    // return the name of the direction based on the enum value for better readability
    switch (DIR) {
        // if the direction is N, return "North"
        case N:
            return "North";
        // if the direction is E, return "East"
        case E:
            return "East";
        // if the direction is S, return "South"
        case S:
            return "South";
        // if the direction is W, return "West"
        case W:
            return "West";
    }
}