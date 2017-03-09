float reading = 0;
float currentValue = 0;
void setup() {
  Serial.begin(115200);

}
void loop() {
  reading = analogRead(A0); //Raw data reading
  currentValue = (reading - 510) * 5 / 1024 / 0.04 - 0.34;
  Serial.println(currentValue);
  delay(800);
}
