/*
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 6
 * Exercise 2
 * Submission code: XXXXXX (provided by your TA-s)
 */

// Define pins
#define LED2 2     // Red LED
#define LED3 3     // Orange LED
#define LED4 4     // Yellow LED
#define LED5 5     // Green LED
#define speaker 6  // Buzzer
#define US_OUT 9   // Ultrasonic HC-SR04 Trig pin
#define US_IN 11   // Ultrasonic HC-SR04 Echo pin

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
int distance;    // Distance in cm
int timer1 = 0;  // Initialize the timer we're using

void setup() {
    // put your setup code here, to run once:
    pinMode(US_OUT, OUTPUT);   // Sets the trigPin as an OUTPUT
    pinMode(US_IN, INPUT);     // Sets the echoPin as an INPUT
    pinMode(LED2, OUTPUT);     // Sets the LED2 as an OUTPUT
    pinMode(LED3, OUTPUT);     // Sets the LED3 as an OUTPUT
    pinMode(LED4, OUTPUT);     // Sets the LED4 as an OUTPUT
    pinMode(LED5, OUTPUT);     // Sets the LED5 as an OUTPUT
    pinMode(speaker, OUTPUT);  // Sets the speaker as an OUTPUT

    Serial.begin(9600);  // Start the serial communication
    setup_timer_1();     // Setup timer 1
}

void loop() { /* Empty, everything is done in the timer interrupt */
}

// Method for setting up timer1
void setup_timer_1() {
    cli();  // stop interrupts

    TCCR1A = 0;  // set entire TCCR1A register to 0
    TCCR1B = 0;  // same for TCCR1B
    TCNT1 = 0;   // initialize counter value to 0

    // calculate at which point to stop the counter and set to int:
    timer1 = (CLOCK_SPEED / (PRESCALER * INTERRUPT_FREQ)) - 1;

    // Check if the timer1 value is within the allowed range
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

    readDistance();                   // Logic for reading the distance
    Serial.print("Distance (cm): ");  // Print the distance
    Serial.println(distance);         // Print the distance
    lightLEDs();                      // Logic for lighting the LEDs
    soundSpeaker();                   // Logic for signing the speaker

    sei();  // allow interrupts
}
/**
 * Method for reading the distance
 * This method sends out a signal and reads the echo
 * to calculate the distance
 *
 * @return void
 **/
void readDistance() {
    digitalWrite(US_OUT, LOW);   // Clear the output pin for 2 microseconds
    delayMicroseconds(2);        // delay for 2 microseconds
    digitalWrite(US_OUT, HIGH);  // Send out a signal to check for echoes for 10 microseconds
    delayMicroseconds(10);       // delay for 10 microseconds
    digitalWrite(US_OUT, LOW);   // Stop signal

    // Read for the echo
    long duration = pulseIn(US_IN, HIGH);
    // Calculate distance
    distance = microsecondsToCentimeters(duration);
}

/**
 * Method for converting microseconds to centimeters
 *
 * @param long microseconds
 * @return long
 **/
long microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 0.034 cm per microsecond.
    // The ping travels out and back, so to find the distance of
    // the object we take half of the distance traveled.
    return (microseconds * 0.034) / 2;
}

/**
 * Method for sounding the speaker
 * This method sounds the speaker if the distance is below 200 cm
 *
 * @return void
 **/
void soundSpeaker() {
    if (distance > 200) {             // If the distance is above 200 cm, mute the speaker
        digitalWrite(speaker, HIGH);  // Mute the speaker, HIGH is off
    } else {                          // If the distance is below 200 cm, sound the speaker
        digitalWrite(speaker, LOW);   // Sound the speaker, LOW is on
        delay(500);                   // Wait for 500 milliseconds
        digitalWrite(speaker, HIGH);  // Mute the speaker, HIGH is off
        delay(100);                   // Wait for 100 milliseconds
    }
}

/**
 * Method for lighting the LEDs
 * This method lights the LEDs according to the distance
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
        delayMicroseconds(DELAY);  // Wait for 10.000 microseconds
        digitalWrite(LED2, LOW);   // Turn off LED 2
        digitalWrite(LED3, LOW);   // Turn off LED 3
        digitalWrite(LED4, LOW);   // Turn off LED 4
        digitalWrite(LED5, LOW);   // Turn off LED 5
        delayMicroseconds(DELAY);  // Wait for 10.000 microseconds
    }
}