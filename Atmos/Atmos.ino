#include <AFMotor.h>

// Motor setup
AF_DCMotor motor1(3); // M3
AF_DCMotor motor2(4); // M4

// Ultrasonic sensor pins
const int trigPin = 10;
const int echoPin = 9;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  motor1.setSpeed(255); // Max speed
  motor2.setSpeed(255);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 15) {
    moveForward();
  } else {
    stopMotors();
    delay(500);

    int leftDist = checkLeft();
    if (leftDist > 15) {
      turnLeft();
      delay(400);
    } else {
      int rightDist = checkRight();
      if (rightDist > 15) {
        turnRight();
        delay(400);
      } else {
        // If both sides are blocked, just stop and wait
        stopMotors();
        delay(1000);
      }
    }

    stopMotors();
    delay(300);
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int distanceCm = duration * 0.034 / 2;
  return distanceCm;
}

int checkLeft() {
  turnLeft();
  delay(300);
  stopMotors();
  delay(200);
  int dist = getDistance();
  delay(200);
  return dist;
}

int checkRight() {
  turnRight();
  delay(600);
  stopMotors();
  delay(200);
  int dist = getDistance();
  delay(200);
  return dist;
}

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
