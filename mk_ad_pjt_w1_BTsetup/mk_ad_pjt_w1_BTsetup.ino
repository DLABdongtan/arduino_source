#include <SoftwareSerial.h>
#define TX  3
#define RX  2
SoftwareSerial BT(RX, TX);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
}

void loop() {
  if(BT.available()) Serial.write(BT.read());
  if(Serial.available()) BT.write(Serial.read());
}