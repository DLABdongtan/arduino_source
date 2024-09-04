#include <LiquidCrystal_I2C.h>
#include <Wire.h>


// 버튼 핀
#define BUTTON_UP     A1  
#define BUTTON_DOWN   A2
#define BUTTON_SEL    A3

//빛 센서 핀
#define LIGHT_SENSOR  A0

//부저 핀
#define BUZZER        6

//LED 핀
#define RED_LED       7
#define YELLOW_LED    8
#define GREEN_LED     9

//초음파 센서 핀
#define TRIGGER  10  //초음파 센서 트리거 핀
#define ECHO     13  // 초음파 센서 에코 핀

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 객체
byte menu = 1; // 메뉴 번호

void setup() {
  lcd.init();  // LCD 준비 설정
  lcd.backlight();
  pinMode(BUTTON_UP, INPUT_PULLUP);  // 버튼 입력모드
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SEL, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT); // 부저핀 출력모드
  pinMode(RED_LED, OUTPUT); // LED 출력모드
  pinMode(YELLOW_LED, OUTPUT); // LED 출력모드
  pinMode(GREEN_LED, OUTPUT); // LED 출력모드
  pinMode(TRIGGER, OUTPUT); // 트리거핀 출력모드
  pinMode(ECHO, INPUT); // 에코핀 입력모드
  initMenu();   // 초기 LCD화면 표시
  updateMenu();  // 현재 LCD 상태 표시
}

void loop() {
 if (digitalRead(BUTTON_DOWN) == 0){ // down버튼 누를시
    menu++;           // menu 1증가
    updateMenu();     // 화면 업데이트
    buttonSound();
    while(digitalRead(BUTTON_DOWN) == 0); // 버튼을 뗄때 까지 기다리기
    delay(50); // 버튼 여러번 인식되는거 방지
  }
  if (digitalRead(BUTTON_UP) == 0){ // up버튼 누를시
    menu--;         // menu 1감소
    updateMenu();   // 화면 업데이트
    buttonSound();
    while(digitalRead(BUTTON_UP) == 0); // 버튼을 뗄때 까지 기다리기
    delay(50); // 버튼 여러번 인식되는거 방지
  }
  if (digitalRead(BUTTON_SEL) == 0){  // sel버튼 누를시(선택버튼)
    buttonSound();
    executeAction();             // 실행할 함수 호출
    updateMenu();             // 화면 업데이트
    while(digitalRead(BUTTON_SEL) == 0); // 버튼을 뗄때 까지 기다리기
    delay(50); // 버튼 여러번 인식되는거 방지
  }
}

void initMenu() {  // 첫 프로그램 실행시, LCD에 프로그램 제목 출력
  lcd.clear(); // 처음에 LCD 화면 모두 지우기
  lcd.setCursor(0,0);
  lcd.print("MultiMenu System");
  lcd.setCursor(8,1);
  lcd.print("3");
  delay(1000);
  lcd.setCursor(8,1);
  lcd.print("2");
  delay(1000);
  lcd.setCursor(8,1);
  lcd.print("1");
  delay(1000);
  lcd.setCursor(5,1);
  lcd.print("Start!");
  delay(1000);
}

void updateMenu() { // 화면 업데이트
  switch(menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">LED ON");
      lcd.setCursor(0, 1);
      lcd.print(" LED OFF");
      break;
    case 2:
      lcd.clear();
      lcd.print(" LED ON");
      lcd.setCursor(0, 1);
      lcd.print(">LED OFF");
      break;
    case 3:
      lcd.clear();
      lcd.print(">CHECK LIGHT");
      lcd.setCursor(0, 1);
      lcd.print(" CHECK DISTANCE");
      break;
    case 4:
      lcd.clear();
      lcd.print(" CHECK LIGHT");
      lcd.setCursor(0, 1);
      lcd.print(">CHECK DISTANCE");
      break;
    case 5:
      menu = 4;
      break;
  }
}

void buttonSound() { // 버튼 누를때 나는 소리
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(10);
}

void executeAction() { // 실행할 함수 모음
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
  }
}

void action1() { // LED를 1초 간격으로 하나씩 켜기
  lcd.clear();
  lcd.print(">Turning On...");
  delay(1000);
  digitalWrite(RED_LED, HIGH);
  delay(1000);
  digitalWrite(YELLOW_LED, HIGH);
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);
  delay(1000);
}
void action2() { // LED를 1초 간격으로 하나씩 끄기
  lcd.clear();
  lcd.print(">Turning Off...");
  delay(1000);
  digitalWrite(GREEN_LED, LOW);
  delay(1000);
  digitalWrite(YELLOW_LED, LOW);
  delay(1000);
  digitalWrite(RED_LED, LOW);
  delay(1000);
}

void action3() { // 빛 세서값을 LCD에 출력
  lcd.clear();
  lcd.print(">ROOM LIGHT VALUE");
  lcd.setCursor(5,1);
  lcd.print(analogRead(LIGHT_SENSOR));
  delay(5000);
}
void action4() { // 초음파 센서 거리값을 LCD에 출력
  lcd.clear();
  lcd.print("DISTANCE(cm)");
  lcd.setCursor(5,1);
  lcd.print(get_cm());
  delay(5000);
}

long get_cm(){ // 초음파 센서로 cm거리 측정
  long duration; 
  digitalWrite(TRIGGER,HIGH); // 센서에 Trig 신호 입력
  delayMicroseconds(10); // 10us 정도 유지
  digitalWrite(TRIGGER,LOW); // Trig 신호 off
  duration = pulseIn(ECHO,HIGH); // Echo pin: HIGH->Low 간격을 측정
  return((long)(340 * duration) / 10000) / 2;  // 거리(cm)로 변환 및 반환
}