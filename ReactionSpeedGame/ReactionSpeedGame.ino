#define BUTTON    2
#define LED1      3
#define LED2      4
#define LED3      5
#define LED4      6
#define LED5      7
#define BUZZER    8

int led_on_position = 0;
unsigned long pTime = 0;
unsigned long interval = 1000;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  delay(1000);
}

void loop() {
  if(digitalRead(BUTTON) == LOW) {
    if(led_on_position == 3) {
      sound_success();
      digitalWrite(LED3, LOW);
      delay(1000);
      led_on_position = 0;
      interval = interval / 1.2;
    }
    else {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      digitalWrite(LED5, HIGH);
      sound_fail();
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, LOW);
      delay(1000);
      interval = 1000;
      led_on_position = 0;
    }
  }

  unsigned long cTime = millis();

  if(cTime - pTime >= interval) {
    pTime = cTime;

    if(led_on_position == 0) {
      digitalWrite(LED5, LOW);
      digitalWrite(LED1, HIGH);
      led_on_position++;
    }
    else if(led_on_position == 1) {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      led_on_position++;
    }
    else if(led_on_position == 2) {
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      led_on_position++;
    }
    else if(led_on_position == 3) {
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      led_on_position++;
    }
    else if(led_on_position == 4) {
      digitalWrite(LED4, LOW);
      digitalWrite(LED5, HIGH);
      led_on_position = 0;
    }
  }
}

void sound_success() {
  digitalWrite(BUZZER, HIGH);
  delay(800);
  digitalWrite(BUZZER, LOW);
}

void sound_fail() {
  for(byte i=0; i<3; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(500);
    digitalWrite(BUZZER, LOW);
    delay(100);
  }
}