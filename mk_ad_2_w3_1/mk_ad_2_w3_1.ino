#include <Adafruit_NeoPixel.h>
#define LED_PIN     6
#define NUMPIXELS   2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PINS, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  pixels.begin();     //led제어 준비
}

void loop() {
  // put your main code here, to run repeatedly:
  white();
  delay(2000);
  off();
  delay(2000);
}

void white() {
  pixels.setBrightness(255);
  pixels.setPixelColor(0,255,255,255);
  pixels.setPixelColor(1,255,255,255);
  pixels.show();
}

void off() {
  pixels.setBrigtness(0);
  pixels.setPixelColor(0,0,0,0);
  pixels.setPixelColor(1,0,0,0);
  pixels.show();
}
