#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial xbee(11, 12); 

const int relay_12v  = 7; // red
const int relay_5v   = 6; // green
const int relay_vnav = 5; // blue
const int relay_3v   = 4; // yellow

bool relay_12v_state  = false;
bool relay_5v_state   = false;
bool relay_vnav_state = false;
bool relay_3v_state   = false;

// read switch state and send number to XBee

const int pin2 = 2;
const int pin3 = 3;
const int pin4 = 4;
const int pin5 = 5;

const int pin6 = 6;
const int pin7 = 7;
const int pin8 = 8;
const int pin9 = 9;

int data = 0;
int state2 = 1;
int state3 = 1;
int state4 = 1;
int state5 = 1;

void setup() {
  xbee.begin(9600);
  pinMode(relay_12v , OUTPUT);
  pinMode(relay_5v  , OUTPUT);
  pinMode(relay_vnav, OUTPUT);
  pinMode(relay_3v,   OUTPUT);

  digitalWrite(relay_12v , relay_12v_state );
  digitalWrite(relay_5v  , relay_5v_state  );
  digitalWrite(relay_vnav, relay_vnav_state);
  digitalWrite(relay_3v  , relay_3v_state  );
  
  Serial.begin(9600);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin5, INPUT);

  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);

}

void loop() {  

  digitalWrite(pin6, HIGH);
  digitalWrite(pin7, HIGH);
  digitalWrite(pin8, HIGH);
  digitalWrite(pin9, HIGH);

  if (digitalRead(pin2) != state2) {
    data = 1;
    relay_12v_state = !relay_12v_state;
    xbee.print('1');
  } 

  if (digitalRead(pin3) != state3) {
    data = 2;
    relay_5v_state = !relay_5v_state;
    xbee.print('2');
  } 

  if (digitalRead(pin4) != state4) {
    data = 3;
    relay_vnav_state = !relay_vnav_state;
    xbee.print('3'); 
  } 

  if (digitalRead(pin5) != state5) {
    data = 4;
    relay_3v_state = !relay_3v_state;
    xbee.print('4');
  } 

  Serial.println(data);

  state2 = digitalRead(pin2);
  state3 = digitalRead(pin3);
  state4 = digitalRead(pin4);
  state5 = digitalRead(pin5);

  // print states (for debugging)
  
  Serial.print("D2 state: ");
  Serial.print(state2);
  Serial.print(" | D3 state: ");
  Serial.print(state3);
  Serial.print(" | D4 state: ");
  Serial.print(state4);
  Serial.print(" | D5 state: ");
  Serial.println(state5);

  // Small delay to prevent spamming the serial monitor too quickly
  delay(1000);

  // send 1234 to XBee if state of switch is 0 (closed)
  if (xbee.available()) {
    Serial.println("available");
  }

  // Set relay states
  digitalWrite(relay_12v , relay_12v_state );
  digitalWrite(relay_5v  , relay_5v_state  );
  digitalWrite(relay_vnav, relay_vnav_state);
  digitalWrite(relay_3v  , relay_3v_state  );

}