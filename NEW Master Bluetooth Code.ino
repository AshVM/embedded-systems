#include <SoftwareSerial.h>

// RX = Pin 10 (Connect to Bluetooth TX)
// TX = Pin 11 (Connect to Bluetooth RX via voltage divider)
SoftwareSerial Bluetooth(10, 11); 

int counter = 0;

void setup() {
  // Start hardware serial for USB debugging
  Serial.begin(9600);
  
  // Default baud rate for HC-05/HC-06 modules
  Bluetooth.begin(9600); 
  
  Serial.println("Bluetooth Master Ready. Sending data...");
}

void loop() {
  // Construct a message
  String message = "Hello Slave! Count: " + String(counter);
  
  // Send message to the Slave Bluetooth module
  Bluetooth.println(message);
  
  // Mirror output to the local Serial Monitor
  Serial.print("Sent: ");
  Serial.println(message);
  
  counter++;
  delay(2000); // Wait 2 seconds before sending again
}
