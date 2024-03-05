/*
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 6
 * Exercise 2
 * Submission code: 969308 (provided by your TA-s)
 */

// Define pins
#define LED2 2        // LED to pin 2
#define LED3 3        // LED to pin 3
#define LED4 4        // LED to pin 4
#define LED5 5        // LED to pin 5
#define speaker 6     // Buzzer
#define ultrasonic 7  // Ultrasonic

// Timer interrupt defines - Taken from course material
// used in calculation: compare match register = [ clock speed/ (prescaler * interrupt frequency) ] - 1
#define PRESCALER 1024        // used for dictating speed of timer according to (timer speed (Hz)) = (Arduino clock speed (16MHz)) / prescaler
#define INTERRUPT_FREQ 1      // define interrupt frequency
#define CLOCK_SPEED 16000000  // Clock speed of the Arduino Uno
#define TIMER1_MAX 65535      // Max counter value for timer1
#define TIMER1_LOW 257        // Lowest counter value for timer1

// Define distance parameters
#define MAX_DIST 200  // 200 cm is when the system starts activating
#define MIN_DIST 25   // 25 cm is when the system is most "annoying" aka imminent danger
#define WARN_DIST 30  // 30 cm is when the system is second-most "annoying" aka almost imminent danger

#define DELAY 10000  // 10.000 microseconds = 0.01 seconds

// Define variables
int distance;    // Distance variable to store the distance from the ultrasonic sensor
int timer1 = 0;  // Initialize the timer we're using

void setup() {
    pinMode(LED2, OUTPUT);     // Set the LED pin 2 as output
    pinMode(LED3, OUTPUT);     // Set the LED pin 3 as output
    pinMode(LED4, OUTPUT);     // Set the LED pin 4 as output
    pinMode(LED5, OUTPUT);     // Set the LED pin 5 as output
    pinMode(speaker, OUTPUT);  // Set the speaker pin as output

    Serial.begin(9600);  // Start the serial communication
    setup_timer_1();     // Set up the timer
}

void loop() {  // Empty loop, everything is done in the ISR
}

void setup_timer_1() {
    cli();  // stop interrupts

    TCCR1A = 0;  // set entire TCCR1A register to 0
    TCCR1B = 0;  // same for TCCR1B
    TCNT1 = 0;   // initialize counter value to 0

    // calculate at which point to stop the counter and set to int:
    timer1 = (CLOCK_SPEED / (PRESCALER * INTERRUPT_FREQ)) - 1;

    if (timer1 >= TIMER1_MAX) {                                                            // if value went above max value
        timer1 = TIMER1_MAX;                                                               // set timer to max allowed value
        Serial.println((String) "timer1 was set too high and was changed to: " + timer1);  // notify user
    } else if (timer1 <= TIMER1_LOW) {                                                     // if value went below lowest value
        timer1 = TIMER1_LOW;                                                               // set timer to max allowed value
        Serial.println((String) "timer1 was set too low and was changed to: " + timer1);   // notify user
    }

    OCR1A = timer1;                       // set compare match register for 1hz increments
    TCCR1B |= (1 << WGM12);               // turn on CTC mode
    TCCR1B |= (1 << CS12) | (1 << CS10);  // set CS10 and CS12 bits for 1024 prescaler
    TIMSK1 |= (1 << OCIE1A);              // enable timer compare interrupt

    sei();  // allow interrupts
}

// ISR method for timer1 interrupts
ISR(TIMER1_COMPA_vect) {
    cli();  // stop interrupts

    readDistance();  // Call the function to read the distance
    // Print the distance
    Serial.print("Distance (cm): ");
    Serial.println(distance);
    lightLEDs();     // Call the function to light the LEDs according to the distance
    soundSpeaker();  // Call the function to sound the speaker

    sei();  // allow interrupts
}

void readDistance() {
    // The following steps follow the assignment description:
    pinMode(ultrasonic, OUTPUT);     // Set Pin to Output
    digitalWrite(ultrasonic, LOW);   // Write a zero to the output to clear the system
    delayMicroseconds(2000);         // Wait 2 milliseconds
    digitalWrite(ultrasonic, HIGH);  // Write a one to the output to send a ping
    delayMicroseconds(10000);        // Wait 10 milliseconds
    digitalWrite(ultrasonic, LOW);   // Write a zero to the output to stop sending the ping

    pinMode(ultrasonic, INPUT);  // Set Pin to Input

    // Listen to input if some echo returns
    long duration = pulseIn(ultrasonic, HIGH);
    // Calculate distance
    // The time until the echo returns is related to the distance of the object from which the ping reflected
    distance = microsecondsToCentimeters(duration);
}

/**
 * Function to convert microseconds to centimeters
 *
 * @param microseconds - the time until the echo returns
 * @return long, the distance of the object from which the ping reflected
 **/
long microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 0.034 cm per microsecond.
    // The ping travels out and back, so to find the distance of the object we
    // take half of the distance traveled.
    return (microseconds * 0.034) / 2;
}

/**
 * Function to sound the speaker
 *
 * @return void
 **/
void soundSpeaker() {
    // Map the distance to the sound, the closer the object, the higher the sound
    int sound = map(distance, 0, 200, 1000, 300);
    if (distance > 200) {      // If the distance is greater than 200 cm, turn off the speaker
        noTone(speaker);       // Turn off the speaker
    } else {                   // If the distance is less than 200 cm, sound the speaker
        tone(speaker, sound);  // Sound the speaker
    }
}

/**
 * Function to light the LEDs according to the distance
 *
 * @return void
 **/
void lightLEDs() {
    // >200 cm - 0 LEDs
    if (distance > 200) {
        digitalWrite(LED2, LOW);  // Turn off LED 2
        digitalWrite(LED3, LOW);  // Turn off LED 3
        digitalWrite(LED4, LOW);  // Turn off LED 4
        digitalWrite(LED5, LOW);  // Turn off LED 5
    }
    // 200 cm and 151 cm - 1 LED
    else if (distance > 150) {
        digitalWrite(LED2, LOW);   // Turn off LED 2
        digitalWrite(LED3, LOW);   // Turn off LED 3
        digitalWrite(LED4, LOW);   // Turn off LED 4
        digitalWrite(LED5, HIGH);  // Turn on LED 5
    }
    // 150 cm and 101 cm - 2 LEDs
    else if (distance > 100) {
        digitalWrite(LED2, LOW);   // Turn off LED 2
        digitalWrite(LED3, LOW);   // Turn off LED 3
        digitalWrite(LED4, HIGH);  // Turn on LED 4
        digitalWrite(LED5, HIGH);  // Turn on LED 5
    }
    // 100 cm and 31 cm - 3 LEDs
    else if (distance > 30) {
        digitalWrite(LED2, LOW);   // Turn off LED 2
        digitalWrite(LED3, HIGH);  // Turn on LED 3
        digitalWrite(LED4, HIGH);  // Turn on LED 4
        digitalWrite(LED5, HIGH);  // Turn on LED 5
    }
    // 30 cm and 26 cm - 4 LEDs
    else if (distance > 24) {
        digitalWrite(LED2, HIGH);  // Turn on LED 2
        digitalWrite(LED3, HIGH);  // Turn on LED 3
        digitalWrite(LED4, HIGH);  // Turn on LED 4
        digitalWrite(LED5, HIGH);  // Turn on LED 5
    }
    // 25 cm and 0 cm - 4 LEDs, blinking
    else {
        digitalWrite(LED2, HIGH);  // Turn on LED 2
        digitalWrite(LED3, HIGH);  // Turn on LED 3
        digitalWrite(LED4, HIGH);  // Turn on LED 4
        digitalWrite(LED5, HIGH);  // Turn on LED 5
        delayMicroseconds(DELAY);  // Wait 0.01 seconds to allow the blinking
        digitalWrite(LED2, LOW);   // Turn off LED 2
        digitalWrite(LED3, LOW);   // Turn off LED 3
        digitalWrite(LED4, LOW);   // Turn off LED 4
        digitalWrite(LED5, LOW);   // Turn off LED 5
        delayMicroseconds(DELAY);  // Wait 0.01 seconds
    }
}