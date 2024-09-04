// LED 핀
#define RED_LED     9
#define YELLOW_LED  10
#define GREEN_LED   11
// 버튼 핀
#define BUTTON1   2
#define BUTTON2   3

void setup() {
  pinMode(RED_LED, OUTPUT);  // LED 출력모드
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP); // 버튼 입력모드
  pinMode(BUTTON2, INPUT_PULLUP);
  attachInterrupt(0, ledOn, FALLING); // BUTTON1 핀 인터럽트 설정
  attachInterrupt(1, ledOff, FALLING); // BUTTON2 핀 인터럽트 설정
}

void loop() {
  // RED LED는 1초 간격으로 on/off
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, HIGH);
  delay(1000);
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  delay(1000);  
}
// 버튼 debounce
void ledOn() { // BUTTON1을 누를시 ISR
  digitalWrite(GREEN_LED, HIGH);
}
void ledOff() { // BUTTON2를 누를시 ISR
  digitalWrite(GREEN_LED, LOW);
}