// =====================================================
//              DRIPGUARD - ESP8266
//   Drop Counting + Dashboard Readings + Wi-Fi
//       LEDs + Buzzer + Python Transmission
// =====================================================

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// ---------------- PIN CONNECTIONS ----------------
const int sensorPin = D5;

const int greenLED = D1;
const int yellowLED = D2;
const int redLED = D3;

const int buzzer = D6;


// ---------------- WIFI SETTINGS ----------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";       // Open Wi-Fi

// Computer running the Python server
const char* serverIP = "YOUR_SERVER_IP";
const int serverPort = 5000;

// Your confirmed Python endpoint
const char* endpoint = "/api/readings";


// ---------------- IV SETTINGS ----------------
float DROP_FACTOR = 20.0;
float BAG_VOLUME = 300.0;
float TARGET_DROPS_PER_MIN = 20.0;

unsigned long lastSettingsFetch = 0;
const unsigned long SETTINGS_INTERVAL = 5000;


// ---------------- DROP VARIABLES ----------------
int lastState = HIGH;

unsigned long totalDrops = 0;
unsigned long dropsThisMinute = 0;


// ---------------- TIMING ----------------
unsigned long lastMinute = 0;

// =====================================================
//          FETCH SETTINGS FROM FLASK
// =====================================================

void fetchSettings() {

  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  WiFiClient client;
  HTTPClient http;

  String url = "http://" + String(serverIP) +
               ":" + String(serverPort) +
               "/api/settings/B01";

  http.begin(client, url);

  int responseCode = http.GET();

  if (responseCode == HTTP_CODE_OK) {

    String response = http.getString();

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, response);

    if (!error && doc["success"] == true) {

      BAG_VOLUME = doc["bag_volume"] | BAG_VOLUME;
      DROP_FACTOR = doc["drip_factor"] | DROP_FACTOR;
      TARGET_DROPS_PER_MIN =
          doc["target_drip_rate"] | TARGET_DROPS_PER_MIN;

      Serial.println("Settings updated from Flask!");

      Serial.print("Bag volume: ");
      Serial.println(BAG_VOLUME);

      Serial.print("Drip factor: ");
      Serial.println(DROP_FACTOR);

      Serial.print("Target rate: ");
      Serial.println(TARGET_DROPS_PER_MIN);
    }
  }

  http.end();
}

// =====================================================
//                     SETUP
// =====================================================

void setup() {

  Serial.begin(9600);

  // Sensor
  pinMode(sensorPin, INPUT);

  // LEDs
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Buzzer
  pinMode(buzzer, OUTPUT);


  // LEDs OFF initially
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  // Active-low buzzer OFF
  digitalWrite(buzzer, HIGH);


  Serial.println();
  Serial.println("=================================");
  Serial.println("       DRIPGUARD STARTED");
  Serial.println("=================================");

  Serial.println("Drop counting started...");


  // ---------------- WIFI ----------------

  Serial.println();
Serial.println("Connecting to Wi-Fi...");

WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);

int attempts = 0;

while (WiFi.status() != WL_CONNECTED && attempts < 40) {
  delay(500);
  Serial.print(".");
  attempts++;
}

Serial.println();

if (WiFi.status() == WL_CONNECTED) {
  Serial.println("Wi-Fi connected!");
  Serial.print("NodeMCU IP: ");
  Serial.println(WiFi.localIP());
} else {
  Serial.println("Wi-Fi connection failed!");
  Serial.print("Wi-Fi status code: ");
  Serial.println(WiFi.status());
}


  // Start first 60-second period
  lastMinute = millis();
}


// =====================================================
//                      LOOP
// =====================================================

void loop() {
    // Fetch updated settings every 5 seconds
  if (millis() - lastSettingsFetch >= SETTINGS_INTERVAL) {
    lastSettingsFetch = millis();
    fetchSettings();
  }

  // ===================================================
  // 1. DETECT AND COUNT DROPS
  // ===================================================

  int currentState = digitalRead(sensorPin);


  // HIGH → LOW = one drop
  if (lastState == HIGH && currentState == LOW) {

    totalDrops++;

    dropsThisMinute++;

    Serial.print("DROP DETECTED | Count = ");
    Serial.println(totalDrops);

    // Debounce
    delay(100);
  }


  lastState = currentState;


  // ===================================================
  // 2. CALCULATE LATEST READING EVERY 60 SECONDS
  // ===================================================

  if (millis() - lastMinute >= 60000) {


    // ---------------- DRIP RATE ----------------

    float dripRate = dropsThisMinute;


    // ---------------- FLOW RATE ----------------

    float flowRate = dripRate / DROP_FACTOR;


    // ---------------- REMAINING VOLUME ----------------

    float deliveredVolume =
      totalDrops / DROP_FACTOR;

    float remainingVolume =
      BAG_VOLUME - deliveredVolume;


    if (remainingVolume < 0) {
      remainingVolume = 0;
    }


    // ---------------- REMAINING TIME ----------------

    float remainingTime = 0;


    if (flowRate > 0) {

      remainingTime =
        remainingVolume / flowRate;
    }


    // =================================================
    // 3. DETERMINE STATUS
    // =================================================

    String status;


    if (dripRate == 0) {

      status = "CRITICAL";

    }

    else if (dripRate >= TARGET_DROPS_PER_MIN * 0.8) {

      status = "NORMAL";

    }

    else {

      status = "ATTENTION";
    }


    // =================================================
    // 4. LEDs + BUZZER
    // =================================================

    if (status == "NORMAL") {

      digitalWrite(greenLED, HIGH);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);

      // Buzzer OFF
      digitalWrite(buzzer, HIGH);
    }


    else if (status == "ATTENTION") {

      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, HIGH);
      digitalWrite(redLED, LOW);

      // Buzzer OFF
      digitalWrite(buzzer, HIGH);
    }


    else {

      digitalWrite(greenLED, LOW);
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, HIGH);

      // Buzzer ON
      digitalWrite(buzzer, LOW);
    }


    // =================================================
    // 5. DISPLAY LATEST READINGS IN SERIAL MONITOR
    // =================================================

    Serial.println();

    Serial.println("========== LATEST READING ==========");


    Serial.print("Bed ID: ");
    Serial.println("B01");


    Serial.print("Drip Rate: ");
    Serial.print(dripRate);
    Serial.println(" drops/min");


    Serial.print("Flow Rate: ");
    Serial.print(flowRate, 2);
    Serial.println(" mL/min");


    Serial.print("Remaining Time: ");
    Serial.print(remainingTime, 2);
    Serial.println(" min");


    Serial.print("Bag Volume: ");
    Serial.print(BAG_VOLUME, 2);
    Serial.println(" mL");


    Serial.print("Status: ");
    Serial.println(status);


    Serial.println("====================================");


    // =================================================
    // 6. SEND LATEST READING TO PYTHON
    // =================================================

    if (WiFi.status() == WL_CONNECTED) {

      WiFiClient client;

      HTTPClient http;


      // Build Python server URL
      String serverURL =
        "http://" +
        String(serverIP) +
        ":" +
        String(serverPort) +
        String(endpoint);


      Serial.println();
      Serial.println("Sending reading to Python...");

      Serial.print("URL: ");
      Serial.println(serverURL);


      // Start HTTP connection
      http.begin(client, serverURL);


      // Tell Python we are sending JSON
      http.addHeader(
        "Content-Type",
        "application/json"
      );


      // =================================================
      // JSON DATA
      // Only the 6 dashboard fields
      // =================================================

      String jsonData = "{";

      jsonData += "\"bed_id\":\"B01\",";
      jsonData += "\"drip_rate\":" + String(dripRate, 2) + ",";
      jsonData += "\"flow_rate\":" + String(flowRate, 2) + ",";
      jsonData += "\"remaining_time\":" + String(remainingTime, 2) + ",";
      jsonData += "\"bag_volume\":" + String(BAG_VOLUME, 2) + ",";
      jsonData += "\"status\":\"" + status + "\"";

      jsonData += "}";


      Serial.print("JSON: ");
      Serial.println(jsonData);


      // Send POST request
      int httpResponseCode =
        http.POST(jsonData);


      // =================================================
      // CHECK PYTHON RESPONSE
      // =================================================

      Serial.print("Python response code: ");
      Serial.println(httpResponseCode);


      if (httpResponseCode > 0) {

        String response =
          http.getString();

        Serial.print("Python response: ");
        Serial.println(response);

      }

      else {

        Serial.print("Transmission failed: ");
        Serial.println(
          http.errorToString(httpResponseCode)
        );
      }


      // Close connection
      http.end();

    }

    else {

      Serial.println(
        "Wi-Fi disconnected. Reading not sent."
      );
    }


    // =================================================
    // 7. START NEXT 60-SECOND PERIOD
    // =================================================

    dropsThisMinute = 0;

    lastMinute = millis();
  }
}
