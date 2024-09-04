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
  Serial.print("potValue: ");
  Serial.println(potValue);
  delay(500);
}