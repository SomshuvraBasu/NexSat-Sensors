// Include the SoftwareSerial library
#include <SoftwareSerial.h>

// Hall effect sensor pins
const int hallDigitalPin = 2;
const int hallAnalogPin = A0;

// XBee module pins
SoftwareSerial xbeeSerial(1, 0); // RX, TX

void setup() {
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  pinMode(hallDigitalPin, INPUT_PULLUP);
}

void loop() {
  // Read the digital value of the hall effect sensor
  int hallDigitalValue = digitalRead(hallDigitalPin);

  // Read the analog value of the hall effect sensor
  int hallAnalogValue = analogRead(hallAnalogPin);

  // Print the sensor values to serial monitor
  Serial.print("Hall effect sensor digital value: ");
  Serial.println(hallDigitalValue);
  Serial.print("Hall effect sensor analog value: ");
  Serial.println(hallAnalogValue);

  // Send the sensor values via XBee
  xbeeSerial.print("Hall effect sensor digital value: ");
  xbeeSerial.println(hallDigitalValue);
  xbeeSerial.print("Hall effect sensor analog value: ");
  xbeeSerial.println(hallAnalogValue);

  // Wait for a moment before the next measurement
  delay(100);
}
