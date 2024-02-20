/**
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 4
 * Exercise 3
 * Submission code: 134256 (provided by your TA-s)
 **/

// Include library for Neopixel ring
#include <Adafruit_NeoPixel.h>

#define NEO_RING 5	// Define pin number for NeoPixel ring
#define redLED 3	// Define pin for red LED
#define tempSensor A0	// Define pin for temperature sensor

// Taken from course material
// used in calculation: compare match register = [ clock speed/ (prescaler * interrupt frequency) ] - 1
#define PRESCALER 1024      // used for dictating speed of timer according to (timer speed (Hz)) = (Arduino clock speed (16MHz)) / prescaler
#define INTERRUPT_FREQ 1    // define interrupt frequency
#define CLOCK_SPEED 16000000// Clock speed of the Arduino Uno
#define TIMER1_MAX 65535    // Max counter value for timer1
#define TIMER1_LOW 257      // Lowest counter value for timer1

/*
Create a variable for the Neo ring
- 1st parameter is the number of LEDs the ring has
- 2nd parameter is the pin the ring is connected to
- 3rd pixel type flags:
	- NEO_GRB = pixels are wired for the GRB bitstream (for most NeoPixel products)
    - NEO_KHZ800 = 800 KHz bitstream (for most NeoPixel products)
*/
Adafruit_NeoPixel ring = Adafruit_NeoPixel(12, NEO_RING, NEO_GRB + NEO_KHZ800);

int timer1 = 0;	// Initialize the timer we're using
int iCounter = 0;	// Initialize the counter

// Function that runs only once
void setup()
{
  pinMode(redLED, OUTPUT);	// Set the red LED pin to output
  ring.begin();	// Initializes all pixels to "off"
  ring.show();	// Clears any lingering data from previous uses
  pinMode(tempSensor, INPUT);	// Set the temp sensor pin to input
  setup_timer_1();        // Setup timer

}

// Function that runs continuously
void loop()
{
  // Do nothing, just wait for interrupts
}

// Timer1 setup function for the interrupts
// Taken from course material
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

// ISR method for timer1 interrupts
ISR(TIMER1_COMPA_vect) {
   cli();     //stop interrupts
  int temperatureVolts = analogRead(tempSensor);	// read the temperature
  float temperatureC = (temperatureVolts - 100)  / 2; // calculate the temp in degrees Celsius

  int lowTemp = 0;	// set the low temp for which to start lighting more LEDs
  int lightUpThreshold = 10;	// How often another LED will light up
  

  // Map the temperature to the number of pixels to light up
  int nr_pixels = map(temperatureC, -40, 125, 1, 12);
  
  ring.clear(); // Clear previous colors
  uint32_t GREEN = ring.Color(0, 255, 0); // Create a variable for green
  ring.fill(GREEN, 0, nr_pixels); // Sets 3rd param amount of pixels starting from 2nd param to color 1st param
  ring.show();	// Show the set colors
  
  // if all pixels are lit up
  if (nr_pixels >= 12) {
    digitalWrite(redLED, HIGH); // Light up the red LED
  }
  // if not all pixels are lit up
  else {
    digitalWrite(redLED, LOW); // Turn off the red LED
  }
  
   sei();     //allow interrupts
}