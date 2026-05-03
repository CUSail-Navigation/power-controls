#include <Arduino.h>
#include <SoftwareSerial.h>

// Some code not currently being used because we
// do not have the boat breadboard right now
SoftwareSerial xbee(11, 12); 

const int panic_button = 10; // Button, need to change this physically
const int boat_status  = 11;
bool panic       = false;
bool boat_status = false;

unsigned long last_status = 0;

const int relay_12v  = 5; // White
const int relay_5v   = 4; // Yellow
const int relay_vnav = 3; // Red
const int relay_3v   = 2; // Blue

bool relay_12v_state  = false;
bool relay_5v_state   = false;
bool relay_vnav_state = false;
bool relay_3v_state   = false;

bool white_state  = false;
bool yellow_state = false;
bool red_state    = false;
bool blue_state   = false;

// Read switch state and send number to XBee

void setup() {
  xbee.begin(9600);
  pinMode(boat_status  , OUTPUT);
  pinMode(panic_button , INPUT_PULLUP);
  pinMode(relay_12v    , OUTPUT      );
  pinMode(relay_5v     , OUTPUT      );
  pinMode(relay_vnav   , OUTPUT      );
  pinMode(relay_3v     , OUTPUT      );

  digitalWrite(relay_12v , relay_12v_state );
  digitalWrite(relay_5v  , relay_5v_state  );
  digitalWrite(relay_vnav, relay_vnav_state);
  digitalWrite(relay_3v  , relay_3v_state  );
  
  Serial.begin(9600);

  // Reads state of LEDs
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

}

void loop() {  

  if (digitalRead(panic_button) == LOW && !panic) {
    panic = true;

    relay_12v_state  = false;
    relay_5v_state   = false;
    relay_vnav_state = false;
    relay_3v_state   = false;

    digitalWrite(relay_12v , LOW);
    digitalWrite(relay_5v  , LOW);
    digitalWrite(relay_vnav, LOW);
    digitalWrite(relay_3v  , LOW);

    delay(200);
  }

  if (panic) {
    return;
  }

  if (xbee.available()) {
    if (xbee.read() == 'W') {
      last_status = millis();
    }
  }

  // Only set boat LED high if it's been less than 7 seconds since last W
  // Slight timeout slack from 5 seconds
  digitalWrite(boat_status, (millis() - last_status < 7000));

  // Before updating state, check if it has changed from before
  // If so, invert relay state and print '1' to Xbee
  // Sequential if statements kind of act as queue already,
  // I think it would be unecessarily complicated to add full FIFO here
  if (digitalRead(6) != white_state) {
    relay_12v_state = !relay_12v_state;
    xbee.print('1');
    delay(200);
  } 

  if (digitalRead(7) != yellow_state) {
    relay_5v_state = !relay_5v_state;
    xbee.print('2');
    delay(200);
  } 

  if (digitalRead(8) != red_state) {
    relay_vnav_state = !relay_vnav_state;
    xbee.print('3'); 
    delay(200);
  } 

  if (digitalRead(9) != blue_state) {
    relay_3v_state = !relay_3v_state;
    xbee.print('4');
    delay(200);
  } 

  // Updates state NOW, using 3.3V as output for breadboarding
  white_state  = digitalRead(6);
  yellow_state = digitalRead(7);
  red_state    = digitalRead(8);
  blue_state   = digitalRead(9);

  // Print states (for debugging)
  Serial.print("White LED state: ");
  Serial.print(white_state);
  Serial.print(" | Yellow LED state: ");
  Serial.print(yellow_state);
  Serial.print(" | Red LED state: ");
  Serial.print(red_state);
  Serial.print(" | Blue LED state: ");
  Serial.println(blue_state);

  Serial.print("Button state: ");
  Serial.println(panic);

  // Small delay to prevent spamming the serial monitor too quickly
  // Should remove before actual use
  delay(1000);

  // Set relay states
  digitalWrite(relay_12v , relay_12v_state );
  digitalWrite(relay_5v  , relay_5v_state  );
  digitalWrite(relay_vnav, relay_vnav_state);
  digitalWrite(relay_3v  , relay_3v_state  );

}