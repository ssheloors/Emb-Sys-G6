/*
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 5
 * Exercise 2
 * Submission code: 777181 (provided by your TA-s)
 */

/**Include DHT libraries to read from the sensor*/
#include <DHT.h>
#include <DHT_U.h>
/**define the pins for the leds*/
#define whiteLED 3 
#define blueLED 4
#define yellowLED 5
#define orangeLED 6
#define redLED 7
/**define the pin for the temperature sensor*/
#define tempSens A0
#define DHTTYPE DHT11 // model of the temperature sensor

DHT dht(tempSens, DHTTYPE); //object of the temperature sensor

void setup() {
  // put your setup code here, to run once:

    /**Set LED pins to output*/
  pinMode(whiteLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  Serial.begin(9600); //begin the serial
  dht.begin(); //begin the reading of the sensor

}

void loop() {

  Serial.println(dht.readTemperature()); //print the temperature
  Serial.println(""); //print a new line

/**define the temperature ranges*/
  int lowTemp = 10; 
  int mediumTemp = 20;
  int highTemp = 30;
  int veryHighTemp = 60;

   float temperatureC = dht.readTemperature(); //read the temperature from the sensor

   if (temperatureC <= lowTemp) { //less or equal than 10 will be white
    digitalWrite(whiteLED, HIGH); //set the white LED to high
    digitalWrite(blueLED, LOW); 
    digitalWrite(yellowLED, LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED, LOW);

  } else if (temperatureC < mediumTemp && temperatureC > lowTemp) { //less than 20 and more than 10 will be blue 
    digitalWrite(whiteLED, HIGH); //set the white LED to high
    digitalWrite(blueLED, HIGH); //set the blue LED to high
    digitalWrite(yellowLED, LOW); //keep off
    digitalWrite(orangeLED, LOW); //keep off
    digitalWrite(redLED, LOW); //keep off
  }
  else if (temperatureC < highTemp && temperatureC > mediumTemp) { //less than 30 and more than 20 will be green
    digitalWrite(whiteLED, HIGH); //set the white LED to high
    digitalWrite(blueLED, HIGH); //set the blue LED to high
    digitalWrite(yellowLED, HIGH); //set the yellow LED to high
    digitalWrite(orangeLED, LOW); //keep off
    digitalWrite(redLED, LOW); //keep off
  }
  else if (temperatureC > highTemp && temperatureC < veryHighTemp) {  //more than 30 and less than 60 will be yellow
    digitalWrite(whiteLED, HIGH); //set the white LED to high
    digitalWrite(blueLED, HIGH); //set the blue LED to high
    digitalWrite(yellowLED, HIGH); //set the yellow LED to high
    digitalWrite(orangeLED, HIGH); //set the orange LED to high
    digitalWrite(redLED, LOW); //keep off
  }

  else if (temperatureC > veryHighTemp) { //more than 60 will be red
    digitalWrite(whiteLED, HIGH); //set the white LED to high
    digitalWrite(blueLED, HIGH); //set the blue LED to high
    digitalWrite(yellowLED, HIGH); //set the yellow LED to high
    digitalWrite(orangeLED, HIGH); //set the orange LED to high
    digitalWrite(redLED, HIGH); //set the red LED to high
  }


  delay(1000); //delay for 1 second
}

