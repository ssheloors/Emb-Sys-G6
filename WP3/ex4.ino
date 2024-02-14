/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 3
 * Exercise 4
 * Submission code: XXXXXX (provided by your TA-s)
 **/

// Include section

#include <Keypad.h> // include the library for accessing the keypad

const int ROW_NUM = 4; //number of rows
const int COLUMN_NUM = 4; //number of columns

char keys [ROW_NUM][COLUMN_NUM] = { //map the keypad in a 2D array
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {13, 12, 11, 10}; //define the pins for the rows
byte pin_column[COLUMN_NUM] = {7, 6, 5, 4};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM); //initialize the keypad


void setup()
{
  Serial.begin(9600); //begin the serial
}

void loop()
{
  char key = keypad.getKey(); //use getkey function to get the key pressed and store it
  
  if(key){ //if a key is pressed
  	Serial.println(key); //print the pressed key
    delay(1000); //delay for 1 second
  }
}