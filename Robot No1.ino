#include <Servo.h>

#define trigPin 3
#define echoPin 2
#define micPin A0
#define ledPin 6
#define servoPin 9

Servo myServo;

int servoPos = 0;
int servoDir = 1;
unsigned long lastServoMove = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(micPin, INPUT);
  pinMode(ledPin, OUTPUT);
  myServo.attach(servoPin);
}

void loop() {
  // Check ultrasonic sensor for movement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 2500);

  if (duration > 0 && duration < 500) {
    if (servoPos < 120 && servoDir == 1) {
      servoPos++;
    } else if (servoPos > 0 && servoDir == -1) {
      servoPos--;
    }
    myServo.write(servoPos);
    lastServoMove = millis();
  }

  // Check microphone sensor for sound
  int micVal = analogRead(micPin);
  if (micVal > 512) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Move servo back and forth
  if (millis() - lastServoMove > 20) {
    if (servoPos == 120) {
      servoDir = -1;
    } else if (servoPos == 0) {
      servoDir = 1;
    }
    servoPos += servoDir;
    myServo.write(servoPos);
    lastServoMove = millis();
  }
}