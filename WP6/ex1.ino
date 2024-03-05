/*
 * (C) Vasilena Karaivanova, Teodora Portase, Marcelo Santibanez, group : 6 (2024)
 * Work package 6
 * Exercise 1
 * Submission code: 969308 (provided by your TA-s)
 */

// Define the pins
#define ENCA 2  // Encoder A
#define ENCB 3  // Encoder B
#define PWM1 5  // Motor pwm 1 pin
#define PWM2 6  // Motor pwm 2 pin

int pos = 0;  // Position in ticks
int deg = 0;  // Position in degrees

int degtarget = 0;  // Target position in degrees

int speed = 0;  // Desired motor speed

int kp = 5;     // Proportional constant for controller (tuning parameter)
int u_out = 0;  // output of controller

int e = 0;  // error
int a = 0;  // a-encoder signal
int b = 0;  // b-encoder signal

// Setup function that will run only once
void setup() {
    Serial.begin(9600);           // Start the serial monitor
    pinMode(ENCA, INPUT_PULLUP);  // Set the encoder A pin as input
    pinMode(ENCB, INPUT_PULLUP);  // Set the encoder B pin as input
    pinMode(PWM1, OUTPUT);        // Set the motor pwm 1 pin as output
    pinMode(PWM2, OUTPUT);        // Set the motor pwm 2 pin as output

    // Attach an interrupt to the encoder A pin to call the ISR_readEncoder function when the pin state changes from LOW to HIGH
    attachInterrupt(digitalPinToInterrupt(ENCA), ISR_readEncoder, RISING);

    // Start the motor, just a tiny little bit because otherwise TinkerCad dies....
    analogWrite(PWM2, 10);
    // Tinkercad seems to work properly without this delay but it is included here for safety
    delay(200);
    analogWrite(PWM1, 10);
}

// Loop function that will run continuously unless error
void loop() {
    // Reset position if it is out of bounds
    if (pos > 2299 || pos < -2299) {  // 2299 is the maximum value of the encoder
        pos = 0;                      // reset the position
    }

    deg = deg % 360;  // Keep the degrees within 0-360

    // Print current position
    Serial.print("The current position is: ");
    Serial.print(deg);
    Serial.print("\n");

    // Get input
    degtarget = getInput();

    // Calculate initial error
    e = degtarget - deg;

    // Loop until error is zero
    while (e) {
        // Map current position into degrees
        deg = map(pos, 0, 2299, 0, 360);

        // Get necessary speed signal
        speed = getAction(e);

        // Send speed signal to motor
        // Rotating clockwise
        if (speed >= 0) {
            if (speed < 100)           // motor does not react with too low inputs
                speed = 100;           // increase the speed to 100
            analogWrite(PWM2, 0);      // stop motor 2 so it rotates clockwise
            analogWrite(PWM1, speed);  // start motor 1 with the new speed
        }

        // Rotating counter-clockwise
        else {
            if (-speed < 100)  // motor does not react with too low inputs
                speed = -100;
            analogWrite(PWM1, 0);       // stop motor 1 so it rotates counter-clockwise
            analogWrite(PWM2, -speed);  // start motor 2 with the new speed
        }

        // Calculate new error
        e = degtarget - deg;
    }

    // When error is zero, stop the motor
    analogWrite(PWM1, 10);
    // This delay will technically prevent the motor from going to the exact degree,
    // since there is a delay between the 2 motors stopping, but this difference is negligible
    // Tinkercad also seems to work properly without this delay but it is included here for safety
    delay(200);
    analogWrite(PWM2, 10);
}

// This function gets the input from the serial monitor
int getInput() {
    int ready = 0;   // flag to check if the input is ready
    char buf[3];     // buffer to store the input, 3 characters are enough for the input since the maximum value is 360
    int input = -1;  // input value

    Serial.print("Please enter the desired position: \n");

    // Wait until the input is ready
    while (!ready) {
        ready = Serial.readBytes(buf, 3);  // read the input and store it in the buffer
        input = atoi(&buf[0]);             // convert the buffer to an integer and store it in the input variable
    }

    return input;  // return the input
}

// This function calculates the necessary speed
int getAction(int error) {
    u_out = kp * error;  // calculates control signal

    if (u_out > 254) {  // u_out cannot be more than 255...
        return 255;
    } else if (u_out < -254) {  //...or less than -254
        return -255;
    } else
        return u_out;  // return the calculated speed
}

// This function is called when the encoder A pin state changes from LOW to HIGH (when the interrupt is triggered)
void ISR_readEncoder() {
    int b = digitalRead(ENCB);  // read the state of the B pin of the encoder and store it in the b variable

    if (b == LOW) {  // if b is low, it is going clockwise
        pos++;       // set position to positive
    } else {         // if B is high, it is going counter-clockwise
        pos--;       // set position to negative
    }
}
