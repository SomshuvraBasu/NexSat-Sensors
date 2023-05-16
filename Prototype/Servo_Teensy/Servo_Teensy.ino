#include <Servo.h>

// Create a Servo object
Servo myservo;

void setup() {
  // Attach the servo to pin 2
  myservo.attach(2);
}

void loop() {
  // Sweep the servo from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }

  // Sweep the servo from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}
