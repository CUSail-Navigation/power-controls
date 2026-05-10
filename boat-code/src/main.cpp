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

  delay(PULSE_MS * 2);

  // Pulse all relays to a known ON state at startup
  for (int i = 0; i < 2; i++) {
    delay(PULSE_MS);
    pulseRelay(relay_12v_on, relay_12v_off, relay_12v_state);
    delay(PULSE_MS);
    pulseRelay(relay_5v_on, relay_5v_off, relay_5v_state);
    delay(PULSE_MS);
    pulseRelay(relay_vnav_on, relay_vnav_off, relay_vnav_state);
    delay(PULSE_MS);
    pulseRelay(relay_3v_on, relay_3v_off, relay_3v_state);
  }
}

void loop() {
  unsigned long currTime = millis();

  if (xbee.available()) {
    char data = xbee.read();

    // Checks current state. If input inverts current state, swap.
    //  12V Relay: 1 = OFF, 2 = ON
    //   5V Relay: 3 = OFF, 4 = ON
    // VNAV Relay: 5 = OFF, 6 = ON
    // 3.3V Relay: 7 = OFF, 8 = ON
    switch (data) {
    case '1':
      if (relay_12v_state == false) {
        pulseRelay(relay_12v_on, relay_12v_off, relay_12v_state);
        xbee.print('1');
      }
      break;
    case '2':
      if (relay_12v_state == true) {
        pulseRelay(relay_12v_on, relay_12v_off, relay_12v_state);
        xbee.print('2');
      }
      break;
    case '3':
      if (relay_5v_state == false) {
        pulseRelay(relay_5v_on, relay_5v_off, relay_5v_state);
        xbee.print('3');
      }
      break;
    case '4':
      if (relay_5v_state == true) {
        pulseRelay(relay_5v_on, relay_5v_off, relay_5v_state);
        xbee.print('4');
      }
      break;
    case '5':
      if (relay_vnav_state == false) {
        pulseRelay(relay_vnav_on, relay_vnav_off, relay_vnav_state);
        xbee.print('5');
      }
      break;
    case '6':
      if (relay_vnav_state == true) {
        pulseRelay(relay_vnav_on, relay_vnav_off, relay_vnav_state);
        xbee.print('6');
      }
      break;
    case '7':
      if (relay_3v_state == false) {
        pulseRelay(relay_3v_on, relay_3v_off, relay_3v_state);
        xbee.print('7');
      }
      break;
    case '8':
      if (relay_3v_state == true) {
        pulseRelay(relay_3v_on, relay_3v_off, relay_3v_state);
        xbee.print('8');
      }
      break;
    }
  }

  // Sends a 'W' every 5 seconds, to indicate the connection is alive
  if (currTime - prevTime > 5000) {
    xbee.print('W');
    prevTime = currTime;
  }
}
