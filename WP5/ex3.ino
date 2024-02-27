/*
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 5
 * Exercise 3
 * Submission code: XXXXX (provided by your TA-s)
 */

// Include section
#include <dht.h>

// Define variables
#define DELAY 1000		// Set delay as 500 milliseconds/0.5 seconds
#define MAX_LIGHT 1023	// Max voltage that can be received

// Define components
#define RED_LED 6		// Set pin 6 for red LED
#define YEL_LED 4		// Set pin 4 for yellow LED
#define GRN_LED 2		// Set pin 2 for green LED
#define TEMP A0			// Set pin A0 for temperature sensor
#define LIGHT A1		// Set pin A1 for light sensor

// Create dht object
dht DHT;

// This will run only once
void setup()
{
  // Set pin 2 for output
  pinMode(RED_LED, OUTPUT);
  // Set pin 4 for output
  pinMode(YEL_LED, OUTPUT);
  // Set pin 6 for output
  pinMode(GRN_LED, OUTPUT);
  // Set pin A0 for input
  pinMode(TEMP, INPUT);
  // Set pin A1 for input
  pinMode(LIGHT, INPUT);
  
  // Start the serial to monitor the light percentage
  Serial.begin(9600);
}

// This will run continuously
void loop()
{
  // Read the temperature from the sensor
  DHT.read11(TEMP);
  // Store the temperature in a variable
  int tempC = DHT.temperature;
  // Print the temperature in the serial
  Serial.print("temperature: "); Serial.println(tempC);
  
  // Read light sensor data
  float lightData = analogRead(LIGHT);
  // Convert data to a percentage of light
  int lightPercent = (lightData * 100.0) / MAX_LIGHT;
  // Print the percentage of light to monitor
  Serial.print("lightPercent: "); Serial.println(lightPercent);
  // Print empty line between outputs for readability
  Serial.println();
  
  // If there is no light
  if (lightPercent == 0) {
    // If the temperature is within normal range
    if(tempC < -12) {
      digitalWrite(RED_LED, LOW);	// Turn off the red LED
      digitalWrite(YEL_LED, LOW);	// Turn off the yellow LED
      digitalWrite(GRN_LED, HIGH);	// Turn on the green LED
    }
    // If the temperature is outside of normal range
    else {
      digitalWrite(RED_LED, HIGH);	// Turn on the red LED
      digitalWrite(YEL_LED, LOW);	// Turn off the yellow LED
      digitalWrite(GRN_LED, LOW);	// Turn off the green LED
    }
  }
  // If the light percent is between 1 and 20
  else if (lightPercent >= 1 && lightPercent <= 20) {
    // If the temperature is below normal range
    if (tempC < -12) {
      digitalWrite(RED_LED, LOW);	// Turn off the red LED
      digitalWrite(YEL_LED, HIGH);	// Turn on the yellow LED
      digitalWrite(GRN_LED, LOW);	// Turn off the green LED
    }
    // If the temperature is above normal range
    else if (tempC > 0) {
      digitalWrite(RED_LED, HIGH);	// Turn on the red LED
      digitalWrite(YEL_LED, LOW);	// Turn off the yellow LED
      digitalWrite(GRN_LED, LOW);	// Turn off the green LED
    }
    // If the temperature is within normal range
    else {
      digitalWrite(RED_LED, LOW);	// Turn off the red LED
      digitalWrite(YEL_LED, LOW);	// Turn off the yellow LED
      digitalWrite(GRN_LED, HIGH);	// Turn on the green LED
    }
  }
  // If the light percent is between 21 and 60
  else if (lightPercent >= 21 && lightPercent <= 60) {
    // If the temperature is above normal range
    if (tempC < 0) {
      digitalWrite(RED_LED, LOW);	// Turn off the red LED
      digitalWrite(YEL_LED, HIGH);	// Turn on the yellow LED
      digitalWrite(GRN_LED, LOW);	// Turn off the green LED
    }
    // If the temperature is above normal range
    else if (tempC > 20) {
      digitalWrite(RED_LED, HIGH);	// Turn on the red LED
      digitalWrite(YEL_LED, LOW);	// Turn off the yellow LED
      digitalWrite(GRN_LED, LOW);	// Turn off the green LED
    }
    // If the temperature is within normal range
    else {
      digitalWrite(RED_LED, LOW);	// Turn off the red LED
      digitalWrite(YEL_LED, LOW);	// Turn off the yellow LED
      digitalWrite(GRN_LED, HIGH);	// Turn on the green LED
    }
  }
  // If the light percent is above 60%
  else {
    // If the temperature is below normal range
    if (tempC < 21) {
      digitalWrite(RED_LED, LOW);	// Turn off the red LED
      digitalWrite(YEL_LED, HIGH);	// Turn on the yellow LED
      digitalWrite(GRN_LED, LOW);	// Turn off the green LED
    }
    // If the temperature is within normal range
    else {
      digitalWrite(RED_LED, LOW);	// Turn off the red LED
      digitalWrite(YEL_LED, LOW);	// Turn off the yellow LED
      digitalWrite(GRN_LED, HIGH);	// Turn on the green LED
    }
  }
  
  // Delay by a specified delay time
  delay(DELAY);
}