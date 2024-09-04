#include <SoftwareSerial.h>
#define BT_TX 3
#define BT_RX 2
SoftwareSerial myBT(BT_RX, BT_TX);

void setup() {
  Serial.begin(9600);
  myBT.begin(9600);
}

void loop() {
  if(myBT.available()) Serial.write(myBT.read());
  if(Serial.available()) myBT.write(Serial.read());
}
