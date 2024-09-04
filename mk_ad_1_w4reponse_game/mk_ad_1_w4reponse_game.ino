
#define BUTTON      2
#define LED1        3
#define LED2        4
#define LED3        5
#define LED4        6
#define LED5        7
#define BUZZER      8

int led_on_position = 0; // led를 on하는 위치 정보(position of led on)
unsigned long pTime = 0; // 과거 시간(previous time)
unsigned long interval = 1000; // 다음번 LED를 켜는 데 걸리는 시간

void setup() {
  pinMode(BUTTON, INPUT_PULLUP); // 버튼 입력모드
  pinMode(LED1, OUTPUT);  // LED 출력모드
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(BUZZER, OUTPUT);  // 부저 출력 모드

  delay(1000);  // 게임 시작 전 1초 기다리기.
 
}

void loop() {  
  if (digitalRead(BUTTON) == LOW) { // 만약 버튼이 눌리면...
    if (led_on_position == 3) {     // 빨간LED에 맞춰 눌렀다면(성공)
      sound_success();   // 성공의 소리 발생
      digitalWrite(LED3, LOW); // LED3 끄기
      delay(1000);  // 1초 잠시 기다리기
      led_on_position = 0;  // led_on_position=0으로 리셋(LED 켜는걸 처음위치로)
      interval = interval / 1.5; // 게임의 속도 증가(LED 점멸 속도 빠르게)
    } 
    else {  // 빨간 LED에 못 맞춰 눌렀다면(실패)
      digitalWrite(LED1, HIGH); // 모든 LED 켜기
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED5, HIGH);

      sound_fail();   // 실패의 소리 발생
      digitalWrite(LED1, LOW); // 모든 LED 끄기
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      
      delay(1000);   // 1초 잠시 기다리기
      interval = 1000;  // 다시 첫 게임의 속도로 돌아가기
      led_on_position = 0; // led_on_position=0으로 리셋(LED 켜는걸 처음위치로)
    }
  }
  unsigned long cTime = millis(); // 현재시간 측정(current time)

  // Function we use instead of delay() so we can turn on LEDs and check
  // if button is pressed at the same time.
  if (cTime - pTime >= interval) { // 매 interval 시간마다 if문 실행이 됨.
      pTime = cTime; // 현재시간은 곧바로 과거 시간이 됨.
      
      if (led_on_position == 0) { // led_on_position = 0 이면
        digitalWrite(LED5, LOW);
        digitalWrite(LED1, HIGH);  // LED1만 켜기
        led_on_position++;         // led_on_position 1증가
      } else if (led_on_position == 1) {  // 1이면
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);  // LED2만 켜기
        led_on_position++;         // led_on_position 1증가
      } else if (led_on_position == 2) { // 2이면
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH); // LED3만 켜기
        led_on_position++;        // led_on_position 1증가
      } else if (led_on_position == 3) {  // 3이면
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, HIGH); // LED4만 켜기
        led_on_position++;        // led_on_position 1증가
      } else if (led_on_position == 4) {  // 3이면
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, HIGH); // LED4만 켜기
        led_on_position = 0;      // led_on_position=0
      }
  }
}

void sound_success() { // 게임 성공시 소리내기
  digitalWrite(BUZZER, HIGH); // 소리발생
  delay(800);               // 0.8초 기다리기(소리 유지)
  digitalWrite(BUZZER, LOW);  // 소리 끄기
}

void sound_fail() {   // 게임 실패시 소리내기
  for(byte i = 0; i < 3; i++) {
    digitalWrite(BUZZER, HIGH); // 소리 발생
    delay(500);               // 0.5초 기다리기(소리 유지)
    digitalWrite(BUZZER, LOW); // 소리 끄기
    delay(100);               // 0.1초 기다리기
  }
}