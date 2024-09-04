#include <SoftwareSerial.h>
#include <Servo.h>
#define SERVO_PIN 9
#define BT_TX     10
#define BT_RX     11

Servo myServo;
SoftwareSerial bt(BT_TX, BT_RX);

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
  bt.begin(9600);
}

void loop() {

  if(bt.available() > 0) {
    int servoPos = bt.read();
    Serial.println(servoPos);
    myServo.write(servoPos);
    delay(10);
  }
}