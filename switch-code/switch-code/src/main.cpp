#include <Arduino.h>

int LEDpin = 2; // or use the predefined LED_BUILTIN
int delayT = 1000; // milliseconds

void setup() {
  // Initialize the digital pin as an output:
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  // Turn the LED on (HIGH voltage level is 5V):
  digitalWrite(LEDpin, HIGH);
  // Wait for a second (1000 milliseconds):
  delay(delayT);
  // Turn the LED off (LOW voltage level is 0V):
  digitalWrite(LEDpin, LOW);
  // Wait for a second:
  delay(delayT);
}