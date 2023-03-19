#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <SD.h>

#define BNO055_SAMPLERATE_DELAY_MS (10)
File dataFile;  // create file object for writing data
Adafruit_BNO055 bno = Adafruit_BNO055();

void setup() {
  Serial.begin(115200);

  if (!SD.begin()) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialization done.");

  dataFile = SD.open("data.txt", FILE_WRITE); // open file for writing
  if (!dataFile) {
    Serial.println("Error opening data.txt for writing.");
    return;
  }
  Serial.println("data.txt opened for writing.");
  dataFile.println("Time (ms),Accelerometer X (m/s^2),Accelerometer Y (m/s^2),Accelerometer Z (m/s^2),Magnetometer X (microtesla),Magnetometer Y (microtesla),Magnetometer Z (microtesla),Gyroscope X (rad/s),Gyroscope Y (rad/s),Gyroscope Z (rad/s)"); // write header

  if (!bno.begin()) {
    Serial.println("BNO055 not detected.");
    while (1);
  }
  bno.setExtCrystalUse(true);
}

void loop() {
  sensors_event_t event;
  bno.getEvent(&event);
  unsigned long time = millis(); // get current time
  Serial.print("Time = "); Serial.print(time);
  Serial.print(", Acceleration (m/s^2) X,Y,Z = ");
  Serial.print(event.acceleration.x); Serial.print(", ");
  Serial.print(event.acceleration.y); Serial.print(", ");
  Serial.print(event.acceleration.z); Serial.print(", ");
  Serial.print("Magnetometer (microtesla) X,Y,Z = ");
  Serial.print(event.magnetic.x); Serial.print(", ");
  Serial.print(event.magnetic.y); Serial.print(", ");
  Serial.print(event.magnetic.z); Serial.print(", ");
  Serial.print("Gyroscope (rad/s) X,Y,Z = ");
  Serial.print(event.gyro.x); Serial.print(", ");
  Serial.print(event.gyro.y); Serial.print(", ");
  Serial.println(event.gyro.z);

  dataFile.print(time); dataFile.print(",");
  dataFile.print(event.acceleration.x); dataFile.print(",");
  dataFile.print(event.acceleration.y); dataFile.print(",");
  dataFile.print(event.acceleration.z); dataFile.print(",");
  dataFile.print(event.magnetic.x); dataFile.print(",");
  dataFile.print(event.magnetic.y); dataFile.print(",");
  dataFile.print(event.magnetic.z); dataFile.print(",");
  dataFile.print(event.gyro.x); dataFile.print(",");
  dataFile.print(event.gyro.y); dataFile.print(",");
  dataFile.println(event.gyro.z);

  delay(BNO055_SAMPLERATE_DELAY_MS); // wait for BNO055 sampling period
}

