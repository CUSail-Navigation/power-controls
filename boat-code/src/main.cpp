#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); 

const int relay_12v  = 7; // red
const int relay_5v   = 6; // green
const int relay_vnav = 5; // blue
const int relay_3v   = 4; // yellow

bool relay_12v_state  = true;
bool relay_5v_state   = true;
bool relay_vnav_state = true;
bool relay_3v_state   = true;

unsigned long prevTime = 0;

void setup() {
  xbee.begin(9600); 

  pinMode(relay_12v , OUTPUT);
  pinMode(relay_5v  , OUTPUT);
  pinMode(relay_vnav, OUTPUT);
  pinMode(relay_3v,   OUTPUT);

  // Init to off state
  digitalWrite(relay_12v , relay_12v_state );
  digitalWrite(relay_5v  , relay_5v_state  );
  digitalWrite(relay_vnav, relay_vnav_state);
  digitalWrite(relay_3v  , relay_3v_state  );
}

void loop() {

  unsigned long currTime = millis();

  // Read from XBee
  if (xbee.available()) {
    char data = xbee.read();

    switch (data) {
    case '1':
        relay_12v_state = !relay_12v_state;
        xbee.print('1');
        break;
    case '2':
        relay_5v_state = !relay_5v_state;
        xbee.print('2');
        break;
    case '3':
        relay_vnav_state = !relay_vnav_state;
        xbee.print('3');
        break;
    case '4':
        relay_3v_state = !relay_3v_state;
        xbee.print('4');
        break;
    }
  }

  // Set relay states
  digitalWrite(relay_12v , relay_12v_state );
  digitalWrite(relay_5v  , relay_5v_state  );
  digitalWrite(relay_vnav, relay_vnav_state);
  digitalWrite(relay_3v  , relay_3v_state  );

  // Write to XBee
  if (currTime - prevTime > 5000) {
    xbee.print('W'); // Send to other XBee
    prevTime = currTime;
  }

}
