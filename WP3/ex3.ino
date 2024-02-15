//
/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 3
 * Exercise 3
 * Submission code: 638180 (provided by your TA-s)
 **/

byte ROW_1 = 13; //define the pin for the first row
byte ROW_2 = 12; //define the pin for the second row
byte ROW_3 = 11; //define the pin for the third row
byte ROW_4 = 10; //define the pin for the fourth row

byte COLUMN_1 = 7; //define the pin for the first column
byte COLUMN_2 = 6; //define the pin for the second column
byte COLUMN_3 = 5; //define the pin for the third column
byte COLUMN_4 = 4; //define the pin for the fourth column

//PROGRAM TO READ KEYPAD INPUT

void setup()
{   
    //set the rows as output to change its  value later
    pinMode(ROW_1, OUTPUT); //first row
    pinMode(ROW_2, OUTPUT); //second row 
    pinMode(ROW_3, OUTPUT); //third row
    pinMode(ROW_4, OUTPUT); //fourth row

    //set the columns as input to read its value later
    pinMode(COLUMN_1, INPUT); //first column
    pinMode(COLUMN_2, INPUT); //second column
    pinMode(COLUMN_3, INPUT); //third column
    pinMode(COLUMN_4, INPUT); //fourth column
    Serial.begin(9600); //begin the serial
  
  
}

void loop()
{
    char key = read_keypad(); //use the read_keypad function to get the key pressed and store it
    if(key != ' '){ //if the value is not empty
      Serial.println(key); //print the pressed key
      delay(1000); //delay for 1 second
    }
  
}

char read_keypad()
{
    char key = ' '; //initialize the key as empty

    //assume that a button in column 1 is pressed by setting the other columns to high
    digitalWrite(ROW_1, LOW); 
    digitalWrite(ROW_2, HIGH); 
    digitalWrite(ROW_3, HIGH);
    digitalWrite(ROW_4, HIGH);

    //check which combination is pressed by checking the value of the columns and set the corresponding key
    if(digitalRead(COLUMN_1) == LOW) key = '1';
    if(digitalRead(COLUMN_2) == LOW) key = '2';
    if(digitalRead(COLUMN_3) == LOW) key = '3';
    if(digitalRead(COLUMN_4) == LOW) key = 'A';
  
    //assume that a button in column 2 is pressed by setting the other columns to high
    digitalWrite(ROW_1, HIGH);
    digitalWrite(ROW_2, LOW);
    digitalWrite(ROW_3, HIGH);
    digitalWrite(ROW_4, HIGH);

    //check which combination is pressed by checking the value of the columns and set the corresponding key
    if(digitalRead(COLUMN_1) == LOW) key = '4';
    if(digitalRead(COLUMN_2) == LOW) key = '5';
    if(digitalRead(COLUMN_3) == LOW) key = '6';
    if(digitalRead(COLUMN_4) == LOW) key = 'B';
  
    //assume that a button in column 3 is pressed by setting the other columns to high
    digitalWrite(ROW_1, HIGH);
    digitalWrite(ROW_2, HIGH);
    digitalWrite(ROW_3, LOW);
    digitalWrite(ROW_4, HIGH);

    //check which combination is pressed by checking the value of the columns and set the corresponding key
    if(digitalRead(COLUMN_1) == LOW) key = '7';
    if(digitalRead(COLUMN_2) == LOW) key = '8';
    if(digitalRead(COLUMN_3) == LOW) key = '9';
    if(digitalRead(COLUMN_4) == LOW) key = 'C';
  
    //assume that a button in column 4 is pressed by setting the other columns to high
    digitalWrite(ROW_1, HIGH);
    digitalWrite(ROW_2, HIGH);
    digitalWrite(ROW_3, HIGH);
    digitalWrite(ROW_4, LOW);

    //check which combination is pressed by checking the value of the columns and set the corresponding key
    if(digitalRead(COLUMN_1) == LOW) key = '*';
    if(digitalRead(COLUMN_2) == LOW) key = '0';
    if(digitalRead(COLUMN_3) == LOW) key = '#';
    if(digitalRead(COLUMN_4) == LOW) key = 'D';
  
    return key; //return the key pressed

    

}