// Ultrasonic sensor pins
const int trigPin = 2;
const int echoPin = 3;

// Sound speed in cm/ms
const float soundSpeed = 0.0343 / 2;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of echo pulse
  float duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  float distance = duration * soundSpeed;

  // Print the distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Wait for a moment before the next measurement
  delay(1000);
}
