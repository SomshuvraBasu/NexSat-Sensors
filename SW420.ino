#define SENSOR_PIN 5  // define the sensor pin
File dataFile;  // create file object for writing data

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
  dataFile.println("Time (ms),Vibration Level"); // write header
}

void loop() {
  unsigned long time = millis(); // get current time
  int vibration = digitalRead(SENSOR_PIN); // read vibration level
  Serial.print("Time = "); Serial.print(time);
  Serial.print(", Vibration Level = "); Serial.println(vibration);

  dataFile.print(time); dataFile.print(",");
  dataFile.println(vibration);

  delay(10); // wait for 10 milliseconds
}

