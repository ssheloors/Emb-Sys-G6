/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 4
 * Exercise 2
 * Submission code: 134256 (provided by your TA-s)
 **/

// Include the library for the servo
#include <Servo.h>

// Define the pin for the servo
#define SERVO A1

// From course material about timer interrupts
// Based on the following tutorial: https://www.instructables.com/Arduino-Timer-Interrupts/
#define TIMER2_MAX 255    // Max counter value for timer2
#define TIMER2_LOW 0      // Lowest counter value for timer2

// Create servo object
Servo servo;
// Initialize timer2
int timer2 = 0;
// Initialize iCounter
int iCounter = 0;
// Degree counter
int degrees = 1;

// Runs only once
void setup()
{
    servo.attach(SERVO);   // Equivalent to pinMode
    servo.write(0);        // Set the initial degrees to 0
    setup_timer_2();       // Setup timer
    Serial.begin(15200);	// Begin serial
}

// Run infinitely
void loop()
{
  delay(500);   // Have a 500 millisecond delay
}

// From course material, and edited for this exercise
// This function sets up timer2 on an Arduino Uno
// Built on top of: https://www.instructables.com/Arduino-Timer-Interrupts/
// Sets timer2 interrupt at 1Hz = 1 second = 1 cycle per second
void setup_timer_2() {

   cli();//stop interrupts

   TCCR2A = 0;	// set entire TCCR2A register to 0
   TCCR2B = 0;	// same for TCCR2B
   TCNT2 = 0; 	//initialize counter value to 0

   // calculate at which point to stop the counter and set to int:
   timer2 = 250;

   if (timer2 >= TIMER2_MAX) {                                                         // if value went above max value
      timer2 = TIMER2_MAX;                                                             // set timer to max allowed value
      Serial.println((String) "timer2 was set too high and was changed to: " + timer2);// notify user
   } else if (timer2 <= TIMER2_LOW) {                                                  // if value went below lowest value
      timer2 = TIMER2_LOW;                                                             // set timer to max allowed value
      Serial.println((String) "timer2 was set too low and was changed to: " + timer2); // notify user
   }

   OCR2A = timer2;                     // set compare match register for 1hz increments
   TCCR2A |= (1 << WGM21);             // turn on CTC mode
   TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);// set CS20, CS21, CS22 bits for 1024 prescaler
   TIMSK2 |= (1 << OCIE2A);            // enable timer compare interrupt

   sei();//allow interrupts
}

// From course material
// Interrupt 1
// Based on setupTimer2, this ISR will trigger every x second(s)
ISR(TIMER2_COMPA_vect) {
   cli();     //stop interrupts
  iCounter++; // increase the value of the iCounter
  if (iCounter < 64) {  // if the time hasn't reached 1 second yet
    return; // exist the function
  }
  servo.write(degrees); // increase the degrees of the servo by 1
  degrees++;            // increase the degrees of the counter by 1
  if(degrees >= 180) {  // if the number of degrees exceeds how much the servo can turn
    degrees = 0;        // reset the servo's degrees
  }
  iCounter = 0;         // set the iCounter back to 0
   sei();     //allow interrupts
}