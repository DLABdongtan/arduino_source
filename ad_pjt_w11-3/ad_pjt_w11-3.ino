const int soilSensorPin = 34;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int soil_value = analogRead(soilSensorPin);
  Serial.print("토양습도 센서값: ");
  Serial.println(soil_value);
  delay(1000);
}
