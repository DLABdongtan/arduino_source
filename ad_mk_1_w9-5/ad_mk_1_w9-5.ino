#define RED_LED     9
#define YELLOW_LED  10
#define GREEN_LED   11
#define POT         A0

void setup() {
    pinMode(RED_LED, OUTPUT);  // LED 출력모드
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
}

void loop() {
    int potValue = analogRead(POT);
    //변환값 
    int Value = map(potValue, 0, 1023, 0, 255);
    //변환값을 LED밝기에 적용하기
    analogWrite(RED_LED, Value);
    analogWrite(YELLOW_LED, Value);
    analogWrite(GREEN_LED, Value);
}
