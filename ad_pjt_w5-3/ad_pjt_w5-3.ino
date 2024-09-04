const int ledPin = 4;
const int buttonPin = 33;
int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  if(buttonState == LOW)  digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
}
