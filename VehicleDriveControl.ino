// Motor A connections
int enable_A = 5;   // Channel 1 and 2 enable: Arduino pin 23, D5/PWM
int input_1 = 3;    // Channel 1 input: Arduino pin 21, D3/GPIO
int input_2 = 4;    // Channel 2 input: Arduino pin 22, D4/GPIO
// Motor B connections
int enable_B = 6;   // Channel 3 and 4 enable: Arduino pin 24, D6/PWM
int input_3 = 7;    // Channel 3 input: Arduino pin 25, D7/GPIO   
int input_4 = 8;    // Channel 4 input: Arduino pin 26, D8/GPIO

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enable_A, OUTPUT);    // Set Arduino pin 23, D5/PWM, as an output pin (L293D pin 1 will receive this output)
  pinMode(enable_B, OUTPUT);    // Set Arduino pin 24, D6/PWM, as an output pin (L293D pin 9 will receive this output)
  pinMode(input_1, OUTPUT);     // Set Arduino pin 21, D3/GPIO, as an output pin (L293D pin 2 will receive this output)
  pinMode(input_2, OUTPUT);     // Set Arduino pin 22, D4/GPIO, as an output pin (L293D pin 7 will receive this output)
  pinMode(input_3, OUTPUT);     // Set Arduino pin 25, D7/GPIO, as an output pin (L293D pin 10 will receive this output)
  pinMode(input_4, OUTPUT);     // Set Arduino pin 26, D8/GPIO, as an output pin (L293D pin 15 will receive this output)

  pinMode(LED_BUILTIN, OUTPUT); // Indicator LED, if the Yellow LED is lit, the code is running

  // Turn off motors - Initialize all input states to LOW
  digitalWrite(input_1, LOW);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, LOW);
  // Turn on Yellow indicator LED to show that code is running
  digitalWrite(LED_BUILTIN, HIGH);
}



void loop() {
  // The argument of the move functions is how many miliseconds the motor moves at full speed, which does not account for accelerationa and decelleration period
  moveForward(2000);            // Moves the motor forward at full speed for two seconds (not counting 1 second speed up and speed down)
  delay(1000);
  moveBackward(2000);           // Moves the motor backward at full speed for two seconds (not counting 1 second speed up and speed down)
  delay(1000);
  moveClockwise(2000);          // Moves the motor clockwise (i.e. right turn) at full speed for two seconds (not counting 1 second speed up and speed down)
  delay(1000);
  moveCounterclockwise(2000);   // Moves the motor counterclockwise (i.e. left turn) at full speed for two seconds (not counting 1 second speed up and speed down)
  delay(1000);
}



// This function moves the vehicle forward
void moveForward(unsigned long inputTime) {
  // Turn on motor A & B in forward direction
  digitalWrite(input_1, HIGH);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, HIGH);
  digitalWrite(input_4, LOW);

  // Accelerate from zero to maximum speed in approximately half a second
  for (int i = 127; i < 256; i++) {
    analogWrite(enable_A, i);
    analogWrite(enable_B, i);
    delay(4);
  }

  // Hold max speed (PWM 255) for the user-specified duration
  analogWrite(enable_A, 255);
  analogWrite(enable_B, 255);
  delay(inputTime);

  // Decelerate from maximum speed to zero in approximatly half a second
  for (int i = 255; i >= 128; --i) {
    analogWrite(enable_A, i);
    analogWrite(enable_B, i);
    delay(4);
  }

  // Turn off motors
  digitalWrite(input_1, LOW);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, LOW);
}

// This function moves the vehicle backwards
void moveBackward(unsigned long inputTime) {
  // Turn on motor A & B in backward direction
  digitalWrite(input_1, LOW);
  digitalWrite(input_2, HIGH);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, HIGH);

  // Accelerate from zero to maximum speed in approximately half a second
  for (int i = 127; i < 256; i++) {
    analogWrite(enable_A, i);
    analogWrite(enable_B, i);
    delay(4);
  }

  // Hold max speed (PWM 255) for the user-specified duration
  analogWrite(enable_A, 255);
  analogWrite(enable_B, 255);
  delay(inputTime);

  // Decelerate from maximum speed to zero in approximatly half a second
  for (int i = 255; i >= 127; --i) {
    analogWrite(enable_A, i);
    analogWrite(enable_B, i);
    delay(4);
  }

  // Turn off motors
  digitalWrite(input_1, LOW);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, LOW);
}

// This function moves the vehicle Clockwise
void moveCounterclockwise(unsigned long inputTime) {
  // Turn on motor A & B in forward direction
  digitalWrite(input_1, HIGH);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, HIGH);

  // Accelerate from zero to maximum speed in approximately half a second
  for (int i = 127; i < 256; i++) {
    analogWrite(enable_A, i);
    analogWrite(enable_B, i);
    delay(4);
  }

  // Hold max speed (PWM 255) for the user-specified duration
  analogWrite(enable_A, 255);
  analogWrite(enable_B, 255);
  delay(inputTime);

  // Decelerate from maximum speed to zero in approximatly half a second
  for (int i = 255; i >= 128; --i) {
    analogWrite(enable_A, i);
    analogWrite(enable_B, i);
    delay(4);
  }

  // Turn off motors
  digitalWrite(input_1, LOW);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, LOW);
}

// This function moves the vehicle Counterclockwise
void moveClockwise(unsigned long inputTime) {
  // Turn on motor A & B in backward direction
  digitalWrite(input_1, LOW);
  digitalWrite(input_2, HIGH);
  digitalWrite(input_3, HIGH);
  digitalWrite(input_4, LOW);

  // Accelerate from zero to maximum speed in approximately half a second
  for (int i = 127; i < 256; i++) {
    analogWrite(enable_A, i);
    analogWrite(enable_B, i);
    delay(4);
  }

  // Hold max speed (PWM 255) for the user-specified duration
  analogWrite(enable_A, 255);
  analogWrite(enable_B, 255);
  delay(inputTime);

  // Decelerate from maximum speed to zero in approximatly half a second
  for (int i = 255; i >= 127; --i) {
    analogWrite(enable_A, i);
    analogWrite(enable_B, i);
    delay(4);
  }

  // Turn off motors
  digitalWrite(input_1, LOW);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, LOW);
}
