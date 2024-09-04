// LED 상태를 저장하는 구조체 정의
struct LEDStatus {
    int pin;
    bool state;
    char name[10];
};

void setup() {
    // 시리얼 통신 시작
    Serial.begin(9600);

    // LED 구조체 변수 선언 및 초기화
    LEDStatus led1;
    led1.pin = LED_BUILTIN;
    led1.state = false; // LED가 꺼져 있는 상태
    strcpy(led1.name, "BUILTIN");

    // LED 핀 모드 설정
    pinMode(led1.pin, OUTPUT);

    // 초기 상태 시리얼 모니터에 출력
    Serial.print("Name: ");
    Serial.println(led1.name);
    Serial.print("Pin: ");
    Serial.println(led1.pin);
    Serial.print("Initial State: ");
    Serial.println(led1.state ? "ON" : "OFF");
}

void loop() {
    // LED 상태를 토글
    static LEDStatus led1 = {LED_BUILTIN, false, "BUILTIN"};

    // LED 상태 변경
    led1.state = !led1.state;
    digitalWrite(led1.pin, led1.state ? HIGH : LOW);

    // 상태를 시리얼 모니터에 출력
    Serial.print("Name: ");
    Serial.println(led1.name);
    Serial.print("Pin: ");
    Serial.println(led1.pin);
    Serial.print("State: ");
    Serial.println(led1.state ? "ON" : "OFF");

    // 1초 대기
    delay(1000);
}