#include <Servo.h>
#define POT_PIN   A0
#define SERVO_PIN 9

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
}

void loop() {
  //print_POT();
  control_servo();
}
void control_servo() {
  int potValue = analogRead(POT_PIN);
  int mapValue = map(potValue, 0, 1023, 0, 180);
  Serial.println(mapValue);
  myServo.write(mapValue);
  delay(10);
}


void print_POT() {
  int potValue = analogRead(POT_PIN);
  Serial.println(potValue);
  delay(100);
}