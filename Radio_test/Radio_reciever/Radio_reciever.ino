#include <SoftwareSerial.h>

const byte rxPin = 4;
const byte txPin = 5;

SoftwareSerial mySerial(rxPin, txPin);

void setup() {

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  mySerial.begin(19200);

  Serial.begin(19200);
  Serial.println("Started!");
}

void loop() {
  while (mySerial.available() == 0) {}
    Serial.println(mySerial.readString());
}