#define RED_LED     9
#define YELLOW_LED  10
#define GREEN_LED   11

void setup() {
  pinMode(RED_LED, OUTPUT); // LED 출력모드
  pinMode(YELLOW_LED, OUTPUT); // LED 출력모드
  pinMode(GREEN_LED, OUTPUT); // LED 출력모드
}

void loop() {
	//여기에 코딩해주세요.
  for(int i=0; i<=255; i++) {
    analogWrite(RED_LED, i);
    delay(10);
  }
  for(int i=0; i<=255; i++) {
    analogWrite(YELLOW_LED, i);
    delay(10);
  }
  for(int i=0; i<=255; i++) {
    analogWrite(GREEN_LED, i);
    delay(10);
  }
  delay(1000);
  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  delay(500);
}