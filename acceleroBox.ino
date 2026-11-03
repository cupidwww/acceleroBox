#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <Adafruit_LSM6DSOX.h>
#include <utility/wifi_drv.h>

#include "predefined.h"
#include "arduino_secrets.h"

Adafruit_LSM6DSOX sox;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

String mqttTopic = String("student/CASA0014/luminaire/") + LIGHT_ID;
String clientId;
byte rgbPayload[PAYLOAD_SIZE];

float smoothedAccel = 9.81f; // gravitational acceleration g = 9.81...
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000) {
      // wait
    delay(10);
  }
  Serial.println(F("Accel -> Vespera LEDs"));

  setupStatusLed();
  setupSensor();
  setupClientId();
  startWifi();

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setBufferSize(512); // 216B + header
  // mqttClient.setKeepAlive(30);

  Serial.print(F("Publishing to topic: "));
  Serial.println(mqttTopic);
}

void loop() {
  ensureConnected();
  mqttClient.loop();

  unsigned long now = millis();
  if (now - lastUpdate < UPDATE_INTERVAL_MS) {
    return;
  }
  lastUpdate = now;

  float rawAccel = readAccelMagnitude();
  smoothedAccel += SMOOTHING_ALPHA * (rawAccel - smoothedAccel);

  Color color = accelToColor(smoothedAccel);
  publishColorToAll(color);

  Serial.print(F("accel="));
  Serial.print(smoothedAccel, 4);
  Serial.print(F(" | RGB="));
  Serial.print(color.r);
  Serial.print(',');
  Serial.print(color.g);
  Serial.print(',');
  Serial.println(color.b);
}
