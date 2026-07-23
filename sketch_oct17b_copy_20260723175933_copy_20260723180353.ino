const int JOY1_X = A0;
const int JOY1_Y = A1;
const int JOY2_X = A2;  // Second joystick X-axis for turning
const int JOY2_Y = A3;  // Second joystick Y-axis (unused, but wired)
const int BUTTON_PIN = 2;

const int CENTER   = 511;
const int DEADZONE = 100;   // ignore small wiggles around center

// 8 Directions for translation
enum { 
  STOP = 0, 
  FORWARD = 1, 
  BACKWARD = 2, 
  LEFT = 3, 
  RIGHT = 4,
  FORWARD_RIGHT = 5,
  FORWARD_LEFT = 6,
  BACKWARD_LEFT = 7,
  BACKWARD_RIGHT = 8 
};

// Turning states
enum {
  TURN_STOP = 0,
  TURN_CW = 1,      // Clockwise (Right)
  TURN_CCW = 2      // Counter-Clockwise (Left)
};

const byte START = 0xFF;
const unsigned long SEND_INTERVAL = 50;  // ms  -> 20 packets/sec
unsigned long lastSend = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial1.begin(9600);   // to HC-05
  Serial.begin(9600);    // USB debug
}

void loop() {
  if (millis() - lastSend < SEND_INTERVAL) return;
  lastSend = millis();

  // --- READ JOYSTICK 1 (DIRECTION) ---
  int x1Val = analogRead(JOY1_X);
  int y1Val = analogRead(JOY1_Y);
  byte btn = (digitalRead(BUTTON_PIN) == LOW) ? 1 : 0;

  // Flipped the axes to reverse the controls
  int dx1 = CENTER - x1Val; 
  int dy1 = CENTER - y1Val;

  byte dir = STOP;

  // Direction Deadzone & Angle Logic
  if (abs(dx1) < DEADZONE && abs(dy1) < DEADZONE) {
    dir = STOP;
  } else {
    float angle = atan2(dy1, dx1) * 180.0 / PI;
    if (angle < 0) angle += 360.0;
    
    angle += 22.5;
    if (angle >= 360.0) angle -= 360.0;

    int sector = angle / 45.0;

    switch (sector) {
      case 0: dir = RIGHT; break;
      case 1: dir = FORWARD_RIGHT; break;
      case 2: dir = FORWARD; break;
      case 3: dir = FORWARD_LEFT; break;
      case 4: dir = LEFT; break;
      case 5: dir = BACKWARD_LEFT; break;
      case 6: dir = BACKWARD; break;
      case 7: dir = BACKWARD_RIGHT; break;
    }
  }

  // --- READ JOYSTICK 2 (TURNING) ---
  int x2Val = analogRead(JOY2_X);
  
  // Flipped the axis to reverse the turning controls
  int dx2 = CENTER - x2Val;
  
  byte tDir = TURN_STOP;
  
  // Turn Deadzone Logic (Only checking the X axis)
  if (abs(dx2) < DEADZONE) {
    tDir = TURN_STOP;
  } else {
    // If pushing right, turn Clockwise. If pushing left, turn Counter-Clockwise.
    tDir = (dx2 > 0) ? TURN_CW : TURN_CCW; 
  }

  // --- PACKET CREATION ---
  // Checksum now includes both dir and tDir
  byte checksum = dir ^ tDir ^ btn;

  // Send exactly 5 bytes
  Serial1.write(START);
  Serial1.write(dir);
  Serial1.write(tDir);
  Serial1.write(btn);
  Serial1.write(checksum);

  // --- DEBUG OUTPUT ---
  Serial.print("dir="); Serial.print(dir);
  Serial.print("\ttDir="); Serial.print(tDir);
  Serial.print("\tbtn="); Serial.println(btn);
}