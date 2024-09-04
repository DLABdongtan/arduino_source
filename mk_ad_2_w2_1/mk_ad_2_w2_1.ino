#include <Servo.h>
#define POT_PIN   A0
#define SERVO_PIN 9

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
}

void loop() {
  print_POT();
}

void print_POT() {
  int potValue = analogRead(POT_PIN);
  Serial.println(potValue);
  delay(100);
}