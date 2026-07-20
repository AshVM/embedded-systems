#include <Wire.h>

// Motor C connections
int enable_C = 5;   // Channel 1 and 2 enable: Arduino pin 23, D5/PWM
int input_5 = 3;    // Channel 1 input: Arduino pin 21, D3/GPIO
int input_6 = 4;    // Channel 2 input: Arduino pin 22, D4/GPIO
// Motor D connections
int enable_D = 6;   // Channel 3 and 4 enable: Arduino pin 24, D6/PWM
int input_7 = 7;    // Channel 3 input: Arduino pin 25, D7/GPIO   
int input_8 = 8;    // Channel 4 input: Arduino pin 26, D8/GPIO

//volatile because values are changed in i2c connection
volatile int backLeft = 0;
volatile int backRight = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // function that executes whenever data is received from writer
  
  pinMode(enable_C, OUTPUT);    // Set Arduino pin 23, D5/PWM, as an output pin (L293D pin 1 will receive this output)
  pinMode(enable_D, OUTPUT);    // Set Arduino pin 24, D6/PWM, as an output pin (L293D pin 9 will receive this output)
  pinMode(input_5, OUTPUT);     // Set Arduino pin 21, D3/GPIO, as an output pin (L293D pin 2 will receive this output)
  pinMode(input_6, OUTPUT);     // Set Arduino pin 22, D4/GPIO, as an output pin (L293D pin 7 will receive this output)
  pinMode(input_7, OUTPUT);     // Set Arduino pin 25, D7/GPIO, as an output pin (L293D pin 10 will receive this output)
  pinMode(input_8, OUTPUT);     // Set Arduino pin 26, D8/GPIO, as an output pin (L293D pin 15 will receive this output)


  pinMode(LED_BUILTIN,OUTPUT);  // sets onBoard LED as output

  // Turn off motors - Initialize all input states to LOW
  digitalWrite(input_5, LOW);
  digitalWrite(input_6, LOW);
  digitalWrite(input_7, LOW);
  digitalWrite(input_8, LOW);

  // Turn on Yellow indicator LED to show that code is running
  digitalWrite(LED_BUILTIN, HIGH);


}

void loop() {
  // put your main code here, to run repeatedly:
  driveMotor(enable_C, input_5, input_6, backLeft);
  driveMotor(enable_D, input_7, input_8, backRight);
  delay(100);
}

void receiveEvent(int howMany) {


}

void driveMotor(int enPin, int inPin1, int inPin2, int speed)
{
  if (speed >= 0) {
    // Motor forward
    digitalWrite(inPin1, HIGH);
    digitalWrite(inPin2, LOW);
    analogWrite(enPin, speed);
  }
  
   else {
    // Motor reverse
    digitalWrite(inPin1, LOW);
    digitalWrite(inPin2, HIGH);
    analogWrite(enPin, -speed);  // Use the magnitude for PWM/ Send absolute value to PWM
  }
}
