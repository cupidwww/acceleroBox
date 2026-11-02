void setupSensor() {
  if (!sox.begin_I2C(SENSOR_ADDRESS)) {
    Serial.println(F("Failed to find LSM6DSOX."));
    setStatusLed(155, 0, 0);
    while (true) {
      delay(10);
    }
  }

  sox.setAccelRange(LSM6DS_ACCEL_RANGE_4_G);
  sox.setAccelDataRate(LSM6DS_RATE_104_HZ);
  Serial.println(F("LSM6DSOX found."));
}

float readAccelMagnitude() {
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  sox.getEvent(&accel, &gyro, &temp);

  float x = accel.acceleration.x;
  float y = accel.acceleration.y;
  float z = accel.acceleration.z;

  // a = sqrt(x^2 + y^2 + z^2)
  return sqrt(x * x + y * y + z * z);
}
