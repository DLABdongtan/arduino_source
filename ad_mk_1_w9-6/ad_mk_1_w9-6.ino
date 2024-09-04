// LED 핀
#define RED_LED     9
#define YELLOW_LED  10
#define GREEN_LED   11
// 버튼 핀
#define BUTTON1   2
#define BUTTON2   3

int brightness = 0; // yellow LED 밝기 변수

void setup() {
  pinMode(RED_LED, OUTPUT);  // LED 출력모드
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP); // 버튼 입력모드
  pinMode(BUTTON2, INPUT_PULLUP); // 버튼 입력모드
  attachInterrupt(0, brighter, FALLING); // BUTTON1 핀 인터럽트 설정
  attachInterrupt(1, darker, FALLING); // BUTTON1 핀 인터럽트 설정
}

void loop() {  
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
  delay(1000);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  delay(1000);
}

void brighter() { // BUTTON1을 누를시 ISR
  brightness++; // 밝기값 증가
  if(brightness > 255) brightness = 255;
  analogWrite(YELLOW_LED, brightness);
}

void darker() { // BUTTON2을 누를시 ISR
  brightness--; // 밝기값 감소
  if(brightness < 0) brightness = 0;
  analogWrite(YELLOW_LED, brightness);
}

