#include <SoftwareSerial.h>
#define RED_LED     2
#define YELLOW_LED  3
#define GREEN_LED   4
#define BT_TX       11
#define BT_RX       10

SoftwareSerial BT(BT_TX, BT_RX);

void setup() {
  // put your setup code here, to run once:
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(BT.available() > 0) {
    byte c = BT.read();
    Serial.println(c);
    if(c == 1)  digitalWrite(RED_LED, HIGH);
    else if(c == 2) digitalWrite(RED_LED, LOW);
    else if(c == 3) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
    }
    else if(c == 4) {
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
    }
  }
}
