const int sensorPin = D5;

int lastState = HIGH;
int dropCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {

  int currentState = digitalRead(sensorPin);

  // A LOW signal means the sensor detected a drop
  if (lastState == HIGH && currentState == LOW) {
    dropCount++;

    Serial.print("DROP DETECTED | Count = ");
    Serial.println(dropCount);

    delay(100);
  }

  lastState = currentState;
}
