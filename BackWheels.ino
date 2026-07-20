#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // function that executes whenever data is received from writer
  pinMode(LED_BUILTIN,OUTPUT);  // sets onBoard LED as output
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}

void receiveEvent(int howMany) {


}