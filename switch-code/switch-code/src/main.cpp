#include <Arduino.h>

#define POSITION_NUM 4
#define ON LOW
#define OFF HIGH

// define the pins connected to the dip switch
const int SWITCH_PINS[] = {9};

void setup() {
  // initialize serial communication
  Serial.begin(9600);

  // set the dip switch pins as inputs with pull-up resistors enabled
  for (int i = 0; i < POSITION_NUM; i++)
    pinMode(SWITCH_PINS[i], INPUT_PULLUP);
}

void loop() {

  // Read the state of each switch position
  for (int i = 0; i < POSITION_NUM; i++) {
    Serial.print("position ");
    Serial.print(i + 1);
    Serial.print(": ");
    int state = digitalRead(SWITCH_PINS[i]);

    if (state == ON)
      Serial.println("ON ");
    else
      Serial.println("OFF ");
  }
  
  Serial.println();

  // add a delay to prevent rapid readings
  delay(500);
}