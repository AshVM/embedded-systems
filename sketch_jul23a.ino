// ==========================================
// FRONT MOTOR DRIVER PINS (Top L293D)
// ==========================================
int front_enA = 5;  // Front Left PWM (Speed)
int front_in1 = 3;  // Front Left Direction A
int front_in2 = 4;  // Front Left Direction B

int front_enB = 6;  // Front Right PWM (Speed)
int front_in3 = 7;  // Front Right Direction A
int front_in4 = 8;  // Front Right Direction B

// ==========================================
// BACK MOTOR DRIVER PINS (Bottom L293D)
// ==========================================
int back_enA = 9;   // Back Left PWM (Speed)
int back_in1 = A0;  // Back Left Direction A
int back_in2 = A1;  // Back Left Direction B

int back_enB = 10;  // Back Right PWM (Speed)
int back_in3 = A2;  // Back Right Direction A
int back_in4 = A3;  // Back Right Direction B

int currentSpeed = 255; // Default max speed

// --- COMMAND ENUMS (Matches Transmitter Exactly) ---
enum { 
  STOP = 0, 
  FORWARD = 1, 
  BACKWARD = 2, 
  LEFT = 3, 
  RIGHT = 4,
  FORWARD_RIGHT = 5,
  FORWARD_LEFT = 6,
  BACKWARD_LEFT = 7,
  BACKWARD_RIGHT = 8,
  TURN_CW = 9,       
  TURN_CCW = 10      
};

// Hold-to-move timer variables
unsigned long lastCommandTime = 0;
const unsigned long commandTimeout = 700; // Safe window higher than master's 500ms delaybyte activeCommand = STOP;

void setup() {
  Serial.begin(9600);  // USB Debug / Monitor
  Serial1.begin(9600); // Bluetooth Receiver (HC-05)

  // Set all motor driver pins to output
  pinMode(front_enA, OUTPUT); pinMode(front_in1, OUTPUT); pinMode(front_in2, OUTPUT);
  pinMode(front_enB, OUTPUT); pinMode(front_in3, OUTPUT); pinMode(front_in4, OUTPUT);

  pinMode(back_enA, OUTPUT); pinMode(back_in1, OUTPUT); pinMode(back_in2, OUTPUT);
  pinMode(back_enB, OUTPUT); pinMode(back_in3, OUTPUT); pinMode(back_in4, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  
  stopMotors();
  digitalWrite(LED_BUILTIN, HIGH); 

  Serial.println("--- Mecanum Slave Ready (Single-Byte Mode) ---");
}

void loop() {
  // --- 1. READ SINGLE BYTE COMMAND ---
  while (Serial1.available() > 0) {
    byte command = Serial1.read();   
      runCommand(command);
      Serial.print(command);
  }
}


// --- 3. COMMAND ROUTER ---
void runCommand(byte cmd) {
  switch(cmd) {
    case STOP:            stopMotors(); break;
    case FORWARD:         moveForward(); break;
    case BACKWARD:        moveBackward(); break;
    case LEFT:            strafeLeft(); break;
    case RIGHT:           strafeRight(); break;
    case FORWARD_RIGHT:   strafeTopRight(); break;
    case FORWARD_LEFT:    strafeTopLeft(); break;
    case BACKWARD_LEFT:   strafeBottomLeft(); break;
    case BACKWARD_RIGHT:  strafeBottomRight(); break;
    case TURN_CW:         rotateClockwise(); break;
    case TURN_CCW:        rotateCounterClockwise(); break;
    default:              stopMotors(); break;
  }
}

// ==========================================
// MECANUM KINEMATICS
// ==========================================
void moveForward() {
  setDirections(1, 1, 1, 1);
  setSpeed(currentSpeed);
}

void moveBackward() {
  setDirections(-1, -1, -1, -1);
  setSpeed(currentSpeed);
}

void strafeLeft() {
  setDirections(-1, 1, 1, -1);
  setSpeed(currentSpeed);
}

void strafeRight() {
  setDirections(1, -1, -1, 1);
  setSpeed(currentSpeed);
}

void strafeTopRight(){
  setDirections(1, 0, 0, 1);
  setSpeed(currentSpeed);
}

void strafeTopLeft(){
  setDirections(0, 1, 1, 0);
  setSpeed(currentSpeed);
}

void strafeBottomLeft(){
  setDirections(-1, 0, 0, -1);
  setSpeed(currentSpeed);
}

void strafeBottomRight(){
  setDirections(0, -1, -1, 0);
  setSpeed(currentSpeed);
}

void rotateClockwise() {
  setDirections(1, -1, 1, -1);
  setSpeed(currentSpeed);
}

void rotateCounterClockwise() {
  setDirections(-1, 1, -1, 1);
  setSpeed(currentSpeed);
}

// ==========================================
// HARDWARE CONTROL HELPERS
// ==========================================
void setSpeed(int speed) {
  analogWrite(front_enA, speed);
  analogWrite(front_enB, speed);
  analogWrite(back_enA, speed);
  analogWrite(back_enB, speed);
}

void setDirections(int fl, int fr, int bl, int br) {
  digitalWrite(front_in1, fl == 1 ? HIGH : LOW);
  digitalWrite(front_in2, fl == -1 ? HIGH : LOW);
  
  digitalWrite(front_in3, fr == 1 ? HIGH : LOW);
  digitalWrite(front_in4, fr == -1 ? HIGH : LOW);
  
  digitalWrite(back_in1, bl == 1 ? HIGH : LOW);
  digitalWrite(back_in2, bl == -1 ? HIGH : LOW);
  
  digitalWrite(back_in3, br == 1 ? HIGH : LOW);
  digitalWrite(back_in4, br == -1 ? HIGH : LOW);
}

void stopMotors() {
  setDirections(0, 0, 0, 0);
  setSpeed(0);
}