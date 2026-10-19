// LEGO LINE FOLLOWER
// Stable Sensors + Turning + Recovery Boost

const int LEFT_SENSOR = 2;
const int RIGHT_SENSOR = 3;

const int LEFT_A = 5;
const int LEFT_B = 6;
const int RIGHT_A = 9;
const int RIGHT_B = 10;

// SPEEDS (0-255)
const int RUN_SPEED = 70;
const int REVERSE_TURN_SPEED = 210;
const int FORWARD_TURN_SPEED = 60;

// MOTOR KICKSTART
const int START_SPEED = 190;
const int KICK_TIME = 35;
const int REVERSE_PAUSE = 20;

// BOOST WHEN RETURNING TO STRAIGHT
const int RECOVERY_SPEED = 200;
const int RECOVERY_TIME = 100;

// SENSOR STATES
const int BLACK = LOW;
const int WHITE = HIGH;

// Movement states
const int STRAIGHT = 0;
const int LEFT_TURN = 1;
const int RIGHT_TURN = 2;

int currentMovement = STRAIGHT;

int leftDirection = 0;
int rightDirection = 0;

void setup() {
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  pinMode(LEFT_A, OUTPUT);
  pinMode(LEFT_B, OUTPUT);
  pinMode(RIGHT_A, OUTPUT);
  pinMode(RIGHT_B, OUTPUT);

  stopMotors();
}

void loop() {
  int left = readStable(LEFT_SENSOR);
  int right = readStable(RIGHT_SENSOR);

  int nextMovement = STRAIGHT;

  if (left == BLACK && right == WHITE) {
    nextMovement = LEFT_TURN;
  }
  else if (left == WHITE && right == BLACK) {
    nextMovement = RIGHT_TURN;
  }

  // Returning to straight after a correction
  if (nextMovement == STRAIGHT &&
      currentMovement != STRAIGHT) {

    recoveryBoost();
  }

  if (nextMovement == LEFT_TURN) {
    turnLeft();
  }
  else if (nextMovement == RIGHT_TURN) {
    turnRight();
  }
  else {
    forward();
  }

  currentMovement = nextMovement;
}

// Majority vote from 5 sensor readings
int readStable(int pin) {
  int total = 0;

  for (int i = 0; i < 5; i++) {
    total += digitalRead(pin);
    delay(1);
  }

  return total >= 3 ? HIGH : LOW;
}

// Drive a motor with direction-change kickstart
void setMotor(int pinA, int pinB,
              int speed, int &lastDirection) {

  int newDirection = 0;

  if (speed > 0) newDirection = 1;
  if (speed < 0) newDirection = -1;

  if (newDirection != 0 &&
      newDirection != lastDirection) {

    analogWrite(pinA, 0);
    analogWrite(pinB, 0);

    if (lastDirection != 0) {
      delay(REVERSE_PAUSE);
    }

    if (newDirection == 1) {
      analogWrite(pinA, START_SPEED);
      analogWrite(pinB, 0);
    }
    else {
      analogWrite(pinA, 0);
      analogWrite(pinB, START_SPEED);
    }

    delay(KICK_TIME);
  }

  if (speed > 0) {
    analogWrite(pinA, speed);
    analogWrite(pinB, 0);
  }
  else if (speed < 0) {
    analogWrite(pinA, 0);
    analogWrite(pinB, -speed);
  }
  else {
    analogWrite(pinA, 0);
    analogWrite(pinB, 0);
  }

  lastDirection = newDirection;
}

void setLeftMotor(int speed) {
  setMotor(LEFT_A, LEFT_B, speed, leftDirection);
}

void setRightMotor(int speed) {
  setMotor(RIGHT_A, RIGHT_B, speed, rightDirection);
}

// Briefly boost BOTH wheels forward
void recoveryBoost() {
  // Stop both wheels before reversing directions
  analogWrite(LEFT_A, 0);
  analogWrite(LEFT_B, 0);
  analogWrite(RIGHT_A, 0);
  analogWrite(RIGHT_B, 0);

  delay(REVERSE_PAUSE);

  // Drive both forward together
  analogWrite(LEFT_A, RECOVERY_SPEED);
  analogWrite(LEFT_B, 0);
  analogWrite(RIGHT_A, RECOVERY_SPEED);
  analogWrite(RIGHT_B, 0);

  delay(RECOVERY_TIME);

  // Both wheels are now moving forward
  leftDirection = 1;
  rightDirection = 1;
}

void forward() {
  setLeftMotor(RUN_SPEED);
  setRightMotor(RUN_SPEED);
}

void turnLeft() {
  setLeftMotor(-REVERSE_TURN_SPEED);
  setRightMotor(FORWARD_TURN_SPEED);
}

void turnRight() {
  setLeftMotor(FORWARD_TURN_SPEED);
  setRightMotor(-REVERSE_TURN_SPEED);
}

void stopMotors() {
  analogWrite(LEFT_A, 0);
  analogWrite(LEFT_B, 0);
  analogWrite(RIGHT_A, 0);
  analogWrite(RIGHT_B, 0);

  leftDirection = 0;
  rightDirection = 0;
}
