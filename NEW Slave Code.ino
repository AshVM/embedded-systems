#include <SoftwareSerial.h>

// RX = Pin 10 (Connect to Bluetooth TX)
// TX = Pin 11 (Connect to Bluetooth RX via voltage divider)
SoftwareSerial Bluetooth(10, 11); 

void setup() {
  // Start hardware serial for USB debugging
  Serial.begin(9600);
  
  // Default baud rate for HC-05/HC-06 modules
  Bluetooth.begin(9600); 
  
  Serial.println("Bluetooth Slave Ready. Waiting for data...");
}

void loop() {
  // Check if data is available from the Bluetooth module
  if (Bluetooth.available()) {
    // Read the incoming string until a newline character (\n) from println
    String receivedData = Bluetooth.readStringUntil('\n');
    
    // Trim extraneous whitespace or carriage return (\r)
    receivedData.trim();
    
    // Print the received message to the Arduino Serial Monitor
    if (receivedData.length() > 0) {
      Serial.print("Received: ");
      Serial.println(receivedData);
    }
  }
}
