/*
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 5
 * Exercise 1
 * Submission code: XXXXXX (provided by your TA-s)
 */

// Define components
#define RED_LED 7	// the red LED is connected to digital pin 8
#define YEL_LED 10	// the yellow LED is connected to pin 10
#define BTN 2		// the button is connected to pin 2

// Setup function that will run only once
void setup()
{
  // Configure connection of the red LED as output
  pinMode(RED_LED, OUTPUT);
  // Configure connection of the yellow LED as output
  pinMode(YEL_LED, OUTPUT);
  // Configure connection of the button as input
  pinMode(BTN, INPUT);

  // Interrupt for button press
  attachInterrupt(digitalPinToInterrupt(BTN), controlLED, CHANGE);
}

// Loop function that will run continuously unless error
void loop()
{
  // Light up the RED_LED
  digitalWrite(RED_LED, HIGH);
  // Wait for 1000 millisecond(s)/ 1 second
  delay(1000);
  // Turn off the LED
  digitalWrite(RED_LED, LOW);
  // Wait for 1000 millisecond(s)/ 1 second
  delay(1000);
}

// Function to change the state of the LED
void controlLED() {
  // If the button is pressed
  if (digitalRead(BTN) == HIGH) {
    // Turn the LED on
    digitalWrite(YEL_LED, HIGH);
  }
  // If the button is not pressed
  else {
    // Turn the LED off
    digitalWrite(YEL_LED, LOW);
  }
}