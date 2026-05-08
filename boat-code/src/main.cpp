#include <Arduino.h>

#define xbee Serial

const int relay_12v_on   = 3;
const int relay_12v_off  = 4;
const int relay_5v_on    = 5;
const int relay_5v_off   = 6;
const int relay_vnav_on  = 7;
const int relay_vnav_off = 8;
const int relay_3v_on    = 9;
const int relay_3v_off   = 10;

bool relay_12v_state  = false;
bool relay_5v_state   = false;
bool relay_vnav_state = false;
bool relay_3v_state   = false;

unsigned long prevTime = 0;

#define PULSE_MS 50

void pulseRelay(int onPin, int offPin, bool &state) {
  int pin = state ? offPin : onPin;
  state = !state;
  digitalWrite(pin, HIGH);
  delay(PULSE_MS);
  digitalWrite(pin, LOW);
}

void setup() {
  xbee.begin(9600);

  int pins[] = {relay_12v_on, relay_12v_off, relay_5v_on, relay_5v_off,
                relay_vnav_on, relay_vnav_off, relay_3v_on, relay_3v_off};
  for (int i = 0; i < 8; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  // Pulse all relays to a known ON state at startup
  int onPins[] = {relay_12v_on, relay_5v_on, relay_vnav_on, relay_3v_on};
  for (int i = 0; i < 4; i++) {
    digitalWrite(onPins[i], HIGH);
    delay(PULSE_MS);
    digitalWrite(onPins[i], LOW);
  }
  relay_12v_state  = true;
  relay_5v_state   = true;
  relay_vnav_state = true;
  relay_3v_state   = true;
}

void loop() {
  unsigned long currTime = millis();

  if (xbee.available()) {
    char data = xbee.read();

    switch (data) {
    case '1':
      pulseRelay(relay_12v_on, relay_12v_off, relay_12v_state);
      xbee.print('1');
      break;
    case '2':
      pulseRelay(relay_5v_on, relay_5v_off, relay_5v_state);
      xbee.print('2');
      break;
    case '3':
      pulseRelay(relay_vnav_on, relay_vnav_off, relay_vnav_state);
      xbee.print('3');
      break;
    case '4':
      pulseRelay(relay_3v_on, relay_3v_off, relay_3v_state);
      xbee.print('4');
      break;
    }
  }

  if (currTime - prevTime > 5000) {
    xbee.print('W');
    prevTime = currTime;
  }
}
