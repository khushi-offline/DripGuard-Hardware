const int sensorPin = D5;

const int greenLED = D1;
const int yellowLED = D2;
const int redLED = D3;

const int buzzer = D6;

// ---------------- SETTINGS ----------------

const float DROP_FACTOR = 20.0;
const float INITIAL_VOLUME = 300.0;

// Prototype/demo target only
const float TARGET_DROPS_PER_MIN = 40.0;

// ---------------- VARIABLES ----------------

int lastState = HIGH;

int dropsThisMinute = 0;
int totalDrops = 0;

unsigned long minuteStart = 0;
unsigned long lastDropTime = 0;

const unsigned long DEBOUNCE = 200;

// ---------------- SETUP ----------------

void setup() {

  Serial.begin(9600);

  pinMode(sensorPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(buzzer, OUTPUT);

  // Everything OFF initially
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  // Your buzzer is active LOW
  digitalWrite(buzzer, HIGH);

  minuteStart = millis();
}

// ---------------- LOOP ----------------

void loop() {

  int currentState = digitalRead(sensorPin);
  unsigned long now = millis();

  // Detect one drop
  if (lastState == HIGH &&
      currentState == LOW &&
      now - lastDropTime >= DEBOUNCE) {

    dropsThisMinute++;
    totalDrops++;

    lastDropTime = now;

    Serial.print("Drop detected | Total = ");
    Serial.println(totalDrops);
  }

  lastState = currentState;

  // Every 60 seconds
  if (now - minuteStart >= 60000) {

    float dropsPerMinute = dropsThisMinute;

    float flowRate = dropsPerMinute / DROP_FACTOR;

    float deliveredVolume = totalDrops / DROP_FACTOR;

    float remainingVolume = INITIAL_VOLUME - deliveredVolume;

    if (remainingVolume < 0) {
      remainingVolume = 0;
    }

    float remainingTime = 0;

    if (flowRate > 0) {
      remainingTime = remainingVolume / flowRate;
    }

    // ---------------- STATUS ----------------

    float lowerNormalLimit = TARGET_DROPS_PER_MIN * 0.90;
    float lowerWarningLimit = TARGET_DROPS_PER_MIN * 0.50;

    // NORMAL
    if (dropsPerMinute >= lowerNormalLimit) {

      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);

      digitalWrite(buzzer, HIGH);

      Serial.println("STATUS = NORMAL");
    }

    // ATTENTION
    else if (dropsPerMinute >= lowerWarningLimit) {

      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redLED, LOW);

      digitalWrite(buzzer, HIGH);

      Serial.println("STATUS = ATTENTION");
    }

    // CRITICAL
    else {

      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);

      digitalWrite(buzzer, LOW);

      Serial.println("STATUS = CRITICAL");
    }

    // ---------------- DISPLAY DATA ----------------

    Serial.println("-------------------------");

    Serial.print("Drops/min = ");
    Serial.println(dropsPerMinute);

    Serial.print("Flow rate = ");
    Serial.print(flowRate);
    Serial.println(" mL/min");

    Serial.print("Total drops = ");
    Serial.println(totalDrops);

    Serial.print("Delivered volume = ");
    Serial.print(deliveredVolume);
    Serial.println(" mL");

    Serial.print("Remaining volume = ");
    Serial.print(remainingVolume);
    Serial.println(" mL");

    Serial.print("Estimated remaining time = ");
    Serial.print(remainingTime);
    Serial.println(" minutes");

    Serial.println("-------------------------");

    // Reset only the one-minute counter
    dropsThisMinute = 0;

    minuteStart = now;
  }

  delay(20);
}
