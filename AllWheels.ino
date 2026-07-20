// Motor A connections
int enable_A = 5;   // Channel 1 and 2 enable: Arduino pin 23, D5/PWM
int input_1 = 3;    // Channel 1 input: Arduino pin 21, D3/GPIO
int input_2 = 4;    // Channel 2 input: Arduino pin 22, D4/GPIO
// Motor B connections
int enable_B = 6;   // Channel 3 and 4 enable: Arduino pin 24, D6/PWM
int input_3 = 7;    // Channel 3 input: Arduino pin 25, D7/GPIO   
int input_4 = 8;    // Channel 4 input: Arduino pin 26, D8/GPIO
// Motor C connections
int enable_C = 9;    // PWM
int input_5 = 11;    // GPIO
int input_6 = 12;    // GPIO
// Motor D connections
int enable_D = 10;   // PWM
int input_7 = A3;    // using A3 as a digital ouput pin  
int input_8 = A4;    // using A4 as a digital ouput pin  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //joystick pin configs
  pinMode(A2, INPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);

  pinMode(enable_A, OUTPUT);    // Set Arduino pin 23, D5/PWM, as an output pin (L293D pin 1 will receive this output)
  pinMode(enable_B, OUTPUT);    // Set Arduino pin 24, D6/PWM, as an output pin (L293D pin 9 will receive this output)
  pinMode(enable_C, OUTPUT);
  pinMode(enable_D, OUTPUT);

  pinMode(input_1, OUTPUT);     // Set Arduino pin 21, D3/GPIO, as an output pin (L293D pin 2 will receive this output)
  pinMode(input_2, OUTPUT);     // Set Arduino pin 22, D4/GPIO, as an output pin (L293D pin 7 will receive this output)
  pinMode(input_3, OUTPUT);     // Set Arduino pin 25, D7/GPIO, as an output pin (L293D pin 10 will receive this output)
  pinMode(input_4, OUTPUT);     // Set Arduino pin 26, D8/GPIO, as an output pin (L293D pin 15 will receive this output)
  pinMode(input_5, OUTPUT);
  pinMode(input_6, OUTPUT);     
  pinMode(input_7, OUTPUT);
  pinMode(input_8, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT); // Indicator LED, if the Yellow LED is lit, the code is running

  // Turn off motors - Initialize all input states to LOW
  digitalWrite(input_1, LOW);
  digitalWrite(input_2, LOW);
  digitalWrite(input_3, LOW);
  digitalWrite(input_4, LOW);
  digitalWrite(input_5, LOW);
  digitalWrite(input_6, LOW);
  digitalWrite(input_7, LOW);
  digitalWrite(input_8, LOW);
  // Turn on Yellow indicator LED to show that code is running
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int joystickx2 = analogRead(A2);
  int joystickx1 = analogRead(A1);
  int joysticky1 = analogRead(A0);

  
  //mapp joystick values to PWM values
  int X = map(joystickx1, 0, 1023, -255, 255);
  int Y = map(joysticky1, 0, 1023, 255, -255);   // invert if pushing forward gives smaller values
  int R = map(joystickx2, 0, 1023, -255, 255);

  //apply joystick deadzone
  if(abs(X) < 20) {
    X = 0;
  }
  if(abs(Y) < 20) {
    Y = 0;
  }
  if(abs(R) < 20) {
    R = 0;
  }
  
  // mecanum wheel
  int frontLeft  = Y + X + R;
  int frontRight = Y - X - R;
  int backLeft   = Y - X + R;
  int backRight  = Y + X - R;

  

  //keep values within PWM range
  frontLeft  = constrain(frontLeft,  -255, 255);
  frontRight = constrain(frontRight, -255, 255);
  backLeft   = constrain(backLeft,   -255, 255);
  backRight  = constrain(backRight,  -255, 255);

  driveMotor(enable_A, input_1, input_2, frontLeft);
  driveMotor(enable_B, input_3, input_4, frontRight);
  driveMotor(enable_C, input_5, input_6, backLeft);
  driveMotor(enable_D, input_7, input_8, backRight);

  delay(10); //stability delay
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