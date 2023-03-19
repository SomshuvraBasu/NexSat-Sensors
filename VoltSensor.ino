const float VCC = 3.3; // Input voltage (in this case 3.3V)
const float R1 = 10000; // Resistance of R1 (10K ohm)
const float R2 = 2200; // Resistance of R2 (2.2K ohm)

void setup() {
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Read analog input on pin A0
  int sensorValue = analogRead(A0);
  
  // Convert sensor value to voltage
  float voltage = sensorValue * VCC / 4095.0;
  
  // Calculate voltage divider output voltage
  float outputVoltage = voltage * (R1 + R2) / R2;

  // Print voltage and output voltage to serial monitor
  Serial.print("Voltage: ");
  Serial.print(voltage, 2); // Round to 2 decimal places
  Serial.print("V, Output Voltage: ");
  Serial.print(outputVoltage, 2); // Round to 2 decimal places
  Serial.println("V");

  delay(1000); // Wait for 1 second
}

