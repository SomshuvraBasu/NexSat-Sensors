#include <SD.h>

const int HALL_PIN = 12; // Hall sensor pin
const int SD_CS_PIN = 5; // CS pin for the SD card

void setup() {
  Serial.begin(9600);
  pinMode(HALL_PIN, INPUT);
  
  // Initialize the SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  
  Serial.println("SD card initialized");
}

void loop() {
  int hallData = digitalRead(HALL_PIN);
  Serial.println(hallData);
  
  // Write hall sensor data to file
  File dataFile = SD.open("hallData.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(hallData);
    dataFile.close();
    Serial.println("Data written to file");
  }
  else {
    Serial.println("Error opening file");
  }
  
  delay(1000);
}

