/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 4
 * Exercise 2
 * Submission code: XXXXXX (provided by your TA-s)
 **/

// Based on the following tutorial: https://www.instructables.com/Arduino-Timer-Interrupts/
#define DATA_RATE 9600// Define data rate for Serial

// used in calculation: compare match register = [ clock speed/ (prescaler * interrupt frequency) ] - 1
#define PRESCALER 1024      // used for dictating speed of timer according to (timer speed (Hz)) = (Arduino clock speed (16MHz)) / prescaler
#define INTERRUPT_FREQ 1    // define interrupt frequency
#define CLOCK_SPEED 16000000// Clock speed of the Arduino Uno
#define TIMER1_MAX 65535    // Max counter value for timer1
#define TIMER1_LOW 257      // Lowest counter value for timer1

#define whiteLED 7
#define blueLED 6
#define greenLED 5
#define yellowLED 4
#define redLED 3
#define tempSensor A0

int timer1 = 0;
int iCounter = 0;

void setup()
{
  pinMode(whiteLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(tempSensor, INPUT);
  Serial.begin(DATA_RATE);// Begin serial
  setup_timer_1();        // Setup timer

}

void loop(){

}

void setup_timer_1() {

   cli();//stop interrupts

   TCCR1A = 0;	// set entire TCCR1A register to 0
   TCCR1B = 0;	// same for TCCR1B
   TCNT1 = 0; 	//initialize counter value to 0

   // calculate at which point to stop the counter and set to int:
   timer1 = (CLOCK_SPEED / (PRESCALER * INTERRUPT_FREQ)) - 1;
   //timer1 = (CLOCK_SPEED / (INTERRUPT_FREQ)) - 1;
   // timer1 = 16 000 000 / 65535

   if (timer1 >= TIMER1_MAX) {                                                         // if value went above max value
      timer1 = TIMER1_MAX;                                                             // set timer to max allowed value
      Serial.println((String) "timer1 was set too high and was changed to: " + timer1);// notify user
   } else if (timer1 <= TIMER1_LOW) {                                                  // if value went below lowest value
      timer1 = TIMER1_LOW;                                                             // set timer to max allowed value
      Serial.println((String) "timer1 was set too low and was changed to: " + timer1); // notify user
   }

   OCR1A = timer1;                     // set compare match register for 1hz increments
   TCCR1B |= (1 << WGM12);             // turn on CTC mode
   TCCR1B |= (1 << CS12) | (1 << CS10);// set CS10 and CS12 bits for 1024 prescaler
   TIMSK1 |= (1 << OCIE1A);            // enable timer compare interrupt

   sei();//allow interrupts
}

ISR(TIMER1_COMPA_vect) {
   cli();     //stop interrupts
  int temperatureVolts = analogRead(tempSensor);
  float temperatureC = (temperatureVolts - 100)  / 2; 

  int lowTemp = 10;
  int mediumTemp = 20;
  int highTemp = 30;
  int veryHighTemp = 60;

  if (temperatureC <= lowTemp) { //less or equal than 10 will be white
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

  } else if (temperatureC < mediumTemp && temperatureC > lowTemp) { //less than 20 and more than 10 will be blue 
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  }
  else if (temperatureC < highTemp && temperatureC > mediumTemp) { //less than 30 and more than 20 will be green
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  }
  else if (temperatureC > highTemp && temperatureC < veryHighTemp) {  //more than 30 and less than 60 will be yellow
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
  }

  else if (temperatureC > veryHighTemp) { //more than 60 will be red
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, HIGH);
  }

  Serial.println((String) "Temperature: " + temperatureC + "C");

   sei();     //allow interrupts
}