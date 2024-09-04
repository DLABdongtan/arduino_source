#define RED_LED     9
#define YELLOW_LED  10
#define GREEN_LED   11

void setup() {
  pinMode(RED_LED, OUTPUT); // LED 출력모드
  pinMode(YELLOW_LED, OUTPUT); // LED 출력모드
  pinMode(GREEN_LED, OUTPUT); // LED 출력모드
}

void loop() {
  for(int i = 0; i <= 255; i++) { // 0 ~ 255 반복
    analogWrite(RED_LED, i); // pwm출력
    delay(50);// LED변화 관찰을 위한 딜레이
  }
  delay(1000);
  for(int i = 255; i > 0; i--) {
    analogWrite(RED_LED, i);
    delay(50);
  }
  delay(1000);
}