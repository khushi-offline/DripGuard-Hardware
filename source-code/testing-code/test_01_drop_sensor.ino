const int sensorPin = D5;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int sensorState = digitalRead(sensorPin);

  if (sensorState == LOW) {
    Serial.println("DETECTED");
  } else {
    Serial.println("NOT DETECTED");
  }

  delay(300);
}
