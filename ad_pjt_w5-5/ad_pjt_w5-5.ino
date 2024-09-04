const int ledPin = 4;
const int potPin = 34;
int potValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  potValue = analogRead(potPin);
  int ledValue = map(potValue, 0, 4095, 0, 255);
  Serial.print("LED light: ");
  Serial.println(ledValue);
  analogWrite(ledPin, ledValue);
  delay(500);
}