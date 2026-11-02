// blue: connecting, green: connected, red: failed
void setupStatusLed() {
    // r 25, g 26, b 27
  WiFiDrv::pinMode(25, OUTPUT);
  WiFiDrv::pinMode(26, OUTPUT);
  WiFiDrv::pinMode(27, OUTPUT);
  setStatusLed(155, 0, 0);
}

void setStatusLed(byte r, byte g, byte b) {
  WiFiDrv::analogWrite(25, r);
  WiFiDrv::analogWrite(26, g);
  WiFiDrv::analogWrite(27, b);
}

void setupClientId() {
  byte mac[6];
  WiFi.macAddress(mac);
  char macStr[13];
  //snprintf(macStr, sizeof(macStr), "%02X%02X%02X%02X%02X%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  //clientId = String("MKR1010_Accel_") + macStr;
  //Serial.print(F("Client ID: "));
  //Serial.println(clientId);
}

void startWifi() {
  setStatusLed(0, 0, 155);
  Serial.print(F("Connecting to WiFi: "));
  Serial.println(SECRET_SSID);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println(F("Communication with WiFi module failed!"));
    setStatusLed(155, 0, 0);
    while (true) {
      delay(10);
    }
  }

  for (int attempt = 0; attempt < 5 && WiFi.status() != WL_CONNECTED; attempt++) {
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    Serial.print('.');
    delay(3000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print(F("\nWiFi connected, IP: "));
    Serial.println(WiFi.localIP());
    setStatusLed(0, 155, 0);
  } else {
    Serial.println(F("\nWiFi connection failed, will retry."));
    setStatusLed(155, 0, 0);
  }
}

void reconnectMqtt() {
  setStatusLed(0, 0, 155);
  wifiClient.stop();
  Serial.println(F("Connecting to MQTT..."));
  if (mqttClient.connect(clientId.c_str(), SECRET_MQTTUSER, SECRET_MQTTPASS)) {
    Serial.println(F("MQTT connected"));
    setStatusLed(0, 155, 0);
  } else {
    Serial.print(F("failed, rc="));
    Serial.print(mqttClient.state());
    Serial.println(F(" try again in 5 seconds"));
    setStatusLed(155, 0, 0);
    delay(5000);
  }
}

void ensureConnected() {
  if (WiFi.status() != WL_CONNECTED) {
    startWifi();
  }
  if (WiFi.status() == WL_CONNECTED && !mqttClient.connected()) {
    reconnectMqtt();
  }
}
