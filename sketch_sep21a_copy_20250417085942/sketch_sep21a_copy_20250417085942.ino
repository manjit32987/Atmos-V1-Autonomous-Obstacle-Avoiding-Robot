#include <AFMotor.h>

AF_DCMotor motor1(3, MOTOR12_1KHZ);
AF_DCMotor motor2(4, MOTOR12_1KHZ);

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

const int safeDistance = 20;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("Smart Avoidance Robot Ready!");
}

void loop() {
  int distance = readDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < safeDistance) {
    Stop();
    delay(1000); // 1 second pause
    scanSides(); // Decide which way to go
  } else {
    forward();
  }
}

void forward() {
  motor1.setSpeed(255); motor1.run(BACKWARD); // Reversed
  motor2.setSpeed(255); motor2.run(BACKWARD); // Reverse

}

void left() {
  motor1.setSpeed(150); motor1.run(BACKWARD);
  motor2.setSpeed(255); motor2.run(FORWARD);
}

void right() {
  motor1.setSpeed(255); motor1.run(FORWARD);
  motor2.setSpeed(150); motor2.run(BACKWARD);
}

void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

// Ultrasonic Distance Reader
int readDistance() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

// Smart Decision-Making
void scanSides() {
  int leftDist = 0, rightDist = 0;

  // Check left
  left();
  delay(500);
  Stop(); delay(300);
  leftDist = readDistance();
  Serial.print("Left distance: "); Serial.println(leftDist);

  // Check right
  right();
  delay(1000); // rotate more since we were already turned left
  Stop(); delay(300);
  rightDist = readDistance();
  Serial.print("Right distance: "); Serial.println(rightDist);

  // Decide which way to go
  if (leftDist > rightDist) {
    left();
    delay(500);
  } else {
    right();
    delay(500);
  }

  Stop(); delay(200);
}
