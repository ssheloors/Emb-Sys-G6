/*
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 5
 * Exercise 2
 * Submission code: XXXXXX (provided by your TA-s)
 */

#include <DHT.h>
#include <DHT_U.h>

#define whiteLED 3
#define blueLED 4
#define yellowLED 5
#define orangeLED 6
#define redLED 7
#define tempSens A0
#define DHTTYPE DHT11

DHT dht(tempSens, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  pinMode(whiteLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  Serial.begin(9600);
  // pinMode(tempSens, INPUT);
  // digitalWrite(tempSens, 1);
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  // controlLED();

  Serial.println(dht.readTemperature());
  // Serial.println(dht.readHumidity());
  Serial.println("");

  int lowTemp = 10;
  int mediumTemp = 20;
  int highTemp = 30;
  int veryHighTemp = 60;

   float temperatureC = dht.readTemperature();

   if (temperatureC <= lowTemp) { //less or equal than 10 will be white
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED, LOW);

  } else if (temperatureC < mediumTemp && temperatureC > lowTemp) { //less than 20 and more than 10 will be blue 
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED, LOW);
  }
  else if (temperatureC < highTemp && temperatureC > mediumTemp) { //less than 30 and more than 20 will be green
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED, LOW);
  }
  else if (temperatureC > highTemp && temperatureC < veryHighTemp) {  //more than 30 and less than 60 will be yellow
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(redLED, LOW);
  }

  else if (temperatureC > veryHighTemp) { //more than 60 will be red
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(redLED, HIGH);
  }


  delay(1000);
}

