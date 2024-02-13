//
byte ROW_1 = 13;
byte ROW_2 = 12;
byte ROW_3 = 11;
byte ROW_4 = 10;

byte COLUMN_1 = 7;
byte COLUMN_2 = 6;
byte COLUMN_3 = 5;
byte COLUMN_4 = 4;

//PROGRAM TO READ KEYPAD INPUT

void setup()
{
    pinMode(ROW_1, OUTPUT);
    pinMode(ROW_2, OUTPUT);
    pinMode(ROW_3, OUTPUT);
    pinMode(ROW_4, OUTPUT);
    pinMode(COLUMN_1, INPUT);
    pinMode(COLUMN_2, INPUT);
    pinMode(COLUMN_3, INPUT);
    pinMode(COLUMN_4, INPUT);
    Serial.begin(9600);
  
  
}

void loop()
{
    char key = read_keypad();
    if(key != ' '){
      Serial.println(key);
      delay(1000);
    }
  
}

char read_keypad()
{
    char key = ' ';

    //assume that a button in column 1 is pressed
    digitalWrite(ROW_1, LOW);
    digitalWrite(ROW_2, HIGH);
    digitalWrite(ROW_3, HIGH);
    digitalWrite(ROW_4, HIGH);

    //check which combination is pressed
    if(digitalRead(COLUMN_1) == LOW) key = '1';
    if(digitalRead(COLUMN_2) == LOW) key = '2';
    if(digitalRead(COLUMN_3) == LOW) key = '3';
    if(digitalRead(COLUMN_4) == LOW) key = 'A';
  
    //assume that a button in column 2 is pressed
    digitalWrite(ROW_1, HIGH);
    digitalWrite(ROW_2, LOW);
    digitalWrite(ROW_3, HIGH);
    digitalWrite(ROW_4, HIGH);

    //check which combination is pressed
    if(digitalRead(COLUMN_1) == LOW) key = '4';
    if(digitalRead(COLUMN_2) == LOW) key = '5';
    if(digitalRead(COLUMN_3) == LOW) key = '6';
    if(digitalRead(COLUMN_4) == LOW) key = 'B';
  
    //assume that a button in column 3 is pressed
    digitalWrite(ROW_1, HIGH);
    digitalWrite(ROW_2, HIGH);
    digitalWrite(ROW_3, LOW);
    digitalWrite(ROW_4, HIGH);

    //check which combination is pressed
    if(digitalRead(COLUMN_1) == LOW) key = '7';
    if(digitalRead(COLUMN_2) == LOW) key = '8';
    if(digitalRead(COLUMN_3) == LOW) key = '9';
    if(digitalRead(COLUMN_4) == LOW) key = 'C';
  
    //assume that a button in column 4 is pressed
    digitalWrite(ROW_1, HIGH);
    digitalWrite(ROW_2, HIGH);
    digitalWrite(ROW_3, HIGH);
    digitalWrite(ROW_4, LOW);

    //check which combination is pressed
    if(digitalRead(COLUMN_1) == LOW) key = '*';
    if(digitalRead(COLUMN_2) == LOW) key = '0';
    if(digitalRead(COLUMN_3) == LOW) key = '#';
    if(digitalRead(COLUMN_4) == LOW) key = 'D';
  
    return key;

    

}