#ifndef CONFIG_H
#define CONFIG_H

struct Color {
  byte r;
  byte g;
  byte b;
};

// test
#define TEST 0

#if TEST
const char* const MQTT_SERVER = "172.20.10.8";
#else
const char* const MQTT_SERVER = "mqtt.cetools.org";
#endif
const int MQTT_PORT = 1884;

const char* const LIGHT_ID = "19";

const int NUM_LEDS = 72;
const int PAYLOAD_SIZE = NUM_LEDS * 3;

const uint8_t SENSOR_ADDRESS = 0x6A;  // DO -> GND
//const uint8_t SENSOR_ADDRESS = 0x6B; // do -> vcc
const float ACCEL_LOW = 9.81f;
const float ACCEL_HIGH = 25.0f;

const float SMOOTHING_ALPHA = 0.2f;
const unsigned long UPDATE_INTERVAL_MS = 50;
#endif // CONFIG_H
