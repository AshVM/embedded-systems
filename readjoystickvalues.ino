void setup() {
  // put your setup code here, to run once:
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valueX = analogRead(A1);
  int valueY = analogRead(A0);

  Serial.print("X-value: " + valueX);
  Serial.print("Y-value: " + valueY);

  delay(1000);
}
