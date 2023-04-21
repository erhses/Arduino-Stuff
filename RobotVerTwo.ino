#include <Servo.h>

const int trigPin = 3;
const int echoPin = 2;
const int servoPin = 9;
const int micPin = 7;
const int ledPin = 6;
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(micPin, INPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  long duration, cm;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  cm = duration / 58;

  if (cm < 20) {
    myServo.write(180); // Move servo to 180 degrees
    delay(250);
    myServo.write(0); // Back to original position ot mimic wave
  } else {
    myServo.write(0); // Move servo to 0 degrees
  }

  int micVal = analogRead(micPin);
  Serial.println(micVal);
  
  if (micVal > 200) { // Mic value threshold
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(500);
}