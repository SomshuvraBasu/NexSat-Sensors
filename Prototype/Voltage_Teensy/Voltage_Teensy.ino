// Voltage sensor pin
const int voltagePin = A0;
// Maximum input voltage of the sensor
const float maxVoltage = 25.0;

void setup() {
  Serial.begin(9600);
  pinMode(voltagePin, INPUT);
}

void loop() {
  // Read the voltage sensor value
  int voltageValue = analogRead(voltagePin);

  // Convert the sensor value to voltage (assuming 5V reference voltage)
  float voltage = ((float)voltageValue * (5.0 / 1023.0)) * (maxVoltage / 5.0);

  // Print the voltage to serial monitor
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  // Wait for a moment before the next measurement
  delay(100);
}
