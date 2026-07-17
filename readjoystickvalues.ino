void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valueX = analogRead(A1);
  int valueY = analogRead(A0);

  Serial.print("X-value: ");
  Serial.println(valueX);
  Serial.print("Y-value: ");
  Serial.println(valueY);

  delay(1000);
}
