# acceleroBox

Project of UCL CASA0014.
The acceleroBox is a card board box with a sensor similar to a black box in a plane.

The wifi connection and mqtt connection use code in https://github.com/ucl-casa-ce/casa0014/blob/main/vespera/workshop-sketch/mkr1010_mqtt_simple/connections.ino.

## Hardware
Arduino board: Arduino MKR WIFI 1010

Sensor: ST LSM6DSOX ([Documentation](https://www.st.com/resource/en/datasheet/lsm6dsox.pdf))

Using I2C wiring for simplification.

## Usage

### Provide credentials
The MQTT server must be reachable from the arduino board. Create `arduino_secrets.h` to provide credentials:

```
#define SECRET_SSID "<network ssid>"
#define SECRET_PASS "<password>"
#define SECRET_MQTTUSER "<mqtt username>"
#define SECRET_MQTTPASS "<mqtt password>"
```

### Compile and upload

This can be done with just one click in Arduino IDE. If using `arduino-cli`(https://github.com/arduino/arduino-cli), install libraries first with:

```
arduino-cli lib install "WiFiNINA" "PubSubClient" "Adafruit LSM6DS"
```

Compile the project:

```
arduino-cli compile --fqbn arduino:samd:mkrwifi1010 .
```

After connecting the board to the computer, find the port using:

```
arduino-cli board list
```

Find the port and upload to it:

```
arduino-cli upload -p <port> --fqbn arduino:samd:mkrwifi1010 .
```

To open the serial monitor:

```
arduino-cli monitor -p <port> -c baudrate=115200
```

where the baudrate could be changed in `Serial.begin(xxx)` in `accel.ino`.
