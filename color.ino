Color accelToColor(float accel) {
  float t = (accel - ACCEL_LOW) / (ACCEL_HIGH - ACCEL_LOW);
  t = constrain(t, 0.0f, 1.0f); // avoid overflow

  Color color;
  color.r = (byte)(255.0f * t + 0.5f);
  color.g = (byte)(255.0f * (1.0f - t) + 0.5f);
  color.b = 0;
  return color;
}

void publishColorToAll(Color color) {
  if (!mqttClient.connected()) {
    return;
  }
  for (int led = 0; led < NUM_LEDS; led++) {
    rgbPayload[led * 3 + 0] = color.r;
    rgbPayload[led * 3 + 1] = color.g;
    rgbPayload[led * 3 + 2] = color.b;
  }
  mqttClient.publish(mqttTopic.c_str(), rgbPayload, PAYLOAD_SIZE);
}
