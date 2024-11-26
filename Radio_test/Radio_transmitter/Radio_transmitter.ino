#include <SoftwareSerial.h>

const byte rxPin = 5;
const byte txPin = 4;

SoftwareSerial mySerial(rxPin, txPin);

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  mySerial.begin(19200);
}

void loop() {

  mySerial.println("Test");

  delay(5000);
}