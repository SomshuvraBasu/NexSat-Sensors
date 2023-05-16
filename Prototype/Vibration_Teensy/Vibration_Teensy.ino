// Vibration sensor pin
const int vibrationPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(vibrationPin, INPUT);
}

void loop() {
  // Read the vibration sensor value
  int vibrationValue = analogRead(vibrationPin);

  // Print the sensor value to serial monitor
  Serial.print("Vibration sensor value: ");
  Serial.println(vibrationValue);

  // Wait for a moment before the next measurement
  delay(100);
}
