#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define SOIL_HUMI   A0
#define RGB_R       10
#define RGB_G       9
#define RGB_B       11
#define PWM_1       6
#define PWM_2       7
#define ON_TIME     2000
#define RX          2
#define TX          3
#define PUMP_OFF    0
#define PUMP_START  170
#define PUMP_MAX    240

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial BT(TX, RX);
unsigned long pm = 0;
int soilHumidity;

void initPin() {
  Serial.begin(9600);
  BT.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(RGB_R, OUTPUT);
  pinMode(RGB_G, OUTPUT);
  pinMode(RGB_B, OUTPUT);
  digitalWrite(RGB_R, LOW);
  digitalWrite(RGB_G, LOW);
  digitalWrite(RGB_B, LOW);
  pinMode(PWM_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  analogWrite(PWM_1, 0);
  digitalWrite(PWM_2, 0);
}

void introLcd() {
  lcd.print("SMART PLANTING");
  lcd.setCursor(0, 1);
  lcd.print("By D.LAB DT");
}

void initLcd() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  introLcd();
}

void printLcd() {
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Moisture : ");
  lcd.print(soilHumidity);
  lcd.print("%");
  lcd.setCursor(0, 1);
  if(soilHumidity < 20) lcd.print("NEED WATER");
  else if(soilHumidity < 50)  lcd.print("SOIL IS DRY");
  else if(soilHumidity < 80)  lcd.print("SOIL IS WET");
  else lcd.print("ENOUGH WATER");
}

void calcSoilHumidity() {
  soilHumidity = map(analogRead(SOIL_HUMI), 1000, 400, 0, 100);
  if(soilHumidity > 100)  soilHumidity = 100;
  else if(soilHumidity < 0) soilHumidity = 0;
}

void writeRGB(bool R, bool G, bool B) {
  digitalWrite(RGB_R, R);
  digitalWrite(RGB_G, G);
  digitalWrite(RGB_B, B);
}

void turnOn_pump() {
  delay(2000);
  lcd.clear();
  lcd.noBacklight();
  delay(250);
  for(int i=PUMP_START; i<PUMP_MAX; i++) {
    analogWrite(PWM_1, i);
    delay(5);
  }
  delay(ON_TIME);
  analogWrite(PWM_1, PUMP_OFF);
  delay(250);
}

void checkBT() {
  if(BT.available() > 0) {
    byte data = BT.read();
    if(data == 1) writeRGB(HIGH, LOW, HIGH);
    else if(data == 2) writeRGB(LOW, LOW, LOW);
    else if(data == 3) turnOn_pump();
  }
}

void setup() {
  // put your setup code here, to run once:
  initPin();
  initLcd();
  delay(ON_TIME);
  writeRGB(HIGH, LOW, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  calcSoilHumidity();
  unsigned long cm = millis();
  if(cm-pm >= 1000) {
    pm = cm;
    BT.print(soilHumidity);
  }
  printLcd();
  checkBT();

  if(soilHumidity < 20) {
    BT.print(soilHumidity);
    delay(1000);
    turnOn_pump();
  }
  else {
    analogWrite(PWM_1, PUMP_OFF);
  }
  delay(ON_TIME);
}
