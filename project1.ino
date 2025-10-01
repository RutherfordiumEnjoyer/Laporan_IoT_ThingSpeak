#include <WiFi.h>
#include "ThingSpeak.h"

const char* WIFI_SSID = "ITS-WIFI-TW2";
const char* WIFI_PASSWORD = "itssurabaya";
unsigned long myChannelNumber = 3095443; // ThingSpeak Channel ID
const char* myWriteAPIKey = "ECIESYMXS3TKRFF1";
// ThingSpeak Write API Key

// Pin definitions
const int TRIG_PIN = 5;  // ESP32 pin connected to the Trig pin of the sensor
const int ECHO_PIN = 18; // ESP32 pin connected to the Echo pin of the sensor
const int LED_PIN = 23;  // ESP32 pin connected to the LED

// Variables for distance calculation
long duration;
float distance_cm;

// ThingSpeak client
WiFiClient client;

// Timer for ThingSpeak updates (ThingSpeak has a 15-second limit for free accounts)
unsigned long lastUpdateTime = 0;
const long updateInterval = 20000; // 20 seconds

void setup() {
  Serial.begin(115200); // Start serial communication for debugging

  // Set pin modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Connect to WiFi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // --- 1. Measure Distance ---
  // Clear the TRIG_PIN condition
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pulse duration
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters
  // Speed of sound = 343 m/s or 0.0343 cm/µs
  // The pulse travels there and back, so we divide by 2
  distance_cm = duration * 0.0343 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // --- 2. Control the LED ---
  if (distance_cm < 10 && distance_cm > 0) {
    // If distance is less than 10 cm, blink the LED
    Serial.println("Object is too close! Blinking LED.");
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  } else {
    // Otherwise, turn the LED off
    digitalWrite(LED_PIN, LOW);
  }

  // --- 3. Send data to ThingSpeak ---
  // Check if it's time to send data (to avoid spamming the server)
  if (millis() - lastUpdateTime > updateInterval) {
    // Set the field you want to update
    ThingSpeak.setField(1, distance_cm);

    // Write to the ThingSpeak channel
    int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (httpCode == 200) {
      Serial.println("Data sent to ThingSpeak successfully.");
    } else {
      Serial.println("Error sending data to ThingSpeak. HTTP error code: " + String(httpCode));
    }
    lastUpdateTime = millis(); // Update the timer
  }

  delay(500); // Small delay to make the loop more stable
}