#include <SoftwareSerial.h>
#include <ArduinoJson.h>

#define ARRAY_SIZE 10

/*
const byte rxPin = 4;
const byte txPin = 3;
const byte enPin = 7;
*/
int NArr[ARRAY_SIZE] = {12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
int PArr[ARRAY_SIZE] = {10, 12, 14, 16, 18, 20, 22, 24, 26, 28};
int KArr[ARRAY_SIZE] = {5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
int AArr[ARRAY_SIZE] = {192, 193, 194, 195, 196, 197, 198, 199, 200, 201};
int RArr[ARRAY_SIZE] = {9600, 9600, 9600, 9600, 9600, 9600, 9600, 9600, 9600, 9600};
/*
SoftwareSerial mySerial(rxPin, txPin);

uint8_t ComN[8] = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};   // N Command
uint8_t ComP[8] = {0x01, 0x03, 0x00, 0x1F, 0x00, 0x01, 0xB5, 0xCC};   // P Command
uint8_t ComK[8] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xC0};   // K Command
uint8_t ComA[8] = {0x01, 0x03, 0x07, 0xD0, 0x00, 0x01, 0x84, 0x87};   // Address
uint8_t ComR[8] = {0x01, 0x03, 0x07, 0xD1, 0x00, 0x01, 0xD5, 0x47};   // Baud rate (0 -> 2400, 1 -> 4800, 2 -> 9600)
*/
void setup() 
{
  /*
    pinMode(enPin, OUTPUT);
    digitalWrite(enPin, LOW);
*/
    Serial.begin(9600);    // Debug serial
    while (!Serial) {} // Vent til serial-forbindelsen er klar
    //mySerial.begin(9600);  // RS485 communication
}

void loop() 
{
    StaticJsonDocument<1024> doc;

    JsonArray N = doc.createNestedArray("N");
    JsonArray P = doc.createNestedArray("P");
    JsonArray K = doc.createNestedArray("K");
    JsonArray A = doc.createNestedArray("A");
    JsonArray R = doc.createNestedArray("R");

    // Tilføj data fra arraysne
    for (int i = 0; i < ARRAY_SIZE; i++) 
    {
      N.add(NArr[i]);
      P.add(PArr[i]);
      K.add(KArr[i]);
      A.add(AArr[i]);
      R.add(RArr[i]);
    }

    // Serialiser JSON til Serial Monitor eller Python
    serializeJson(doc, Serial);
    Serial.println(); // Tilføj en ny linje for at markere slutningen af JSON

    delay(500); // Send data hver 5. sekund
}

/*void saveJsonToFile() 
{
  StaticJsonDocument<1024> jsonDoc; // Dokument med plads til 1024 bytes
  jsonDoc["N"] = NArr;
  jsonDoc["P"] = PArr;
  jsonDoc["K"] = KArr;

  // Konverter JSON til en streng
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  Serial.println()
}

int readSensorValue(uint8_t *command, const char *label) {
    uint8_t data[7] = {0};
    int retries = 3;

    while (retries--) {
        digitalWrite(enPin, HIGH);
        mySerial.write(command, 8);  // Send query frame
        digitalWrite(enPin, LOW);
        delay(10);  // Give sensor time to switch from transmit to receive

        // Wait for the response
        int bytesRead = readSerialData(data, 7, label);
        if (bytesRead == 7) {
            if (data[0] == 0x01 && data[1] == 0x03 && data[2] == 0x02) {
                if (CRC16_2(data, 5) == (data[5] | (data[6] << 8))) {
                    int value = (data[3] << 8) | data[4];
                    Serial.print(label);
                    Serial.print(" Value: ");
                    Serial.println(value);

                    // Debug raw data in decimal
                    Serial.print("Raw Data: ");
                    Serial.print("High Byte = ");
                    Serial.print(data[3], DEC);
                    Serial.print(", Low Byte = ");
                    Serial.println(data[4], DEC);

                  return value;
                } else {
                    Serial.println("CRC mismatch");
                }
            } else {
                Serial.println("Invalid response structure");
            }
        } else {
            Serial.println("Incomplete response or timeout");
        }

        mySerial.flush();  // Clear buffer for the next attempt
        delay(100);  // Short delay before retry
    }
    return -1;  // Return error after retries
}

int readSerialData(uint8_t *buf, size_t len, const char *label) {
    size_t offset = 0;
    size_t left = len;
    int timeout = 1000;  // Increased timeout for slow responses
    long start = millis();

    while (left && millis() - start < timeout) {
        if (mySerial.available()) {
            buf[offset++] = mySerial.read();
            left--;
        }
    }

    // Debugging: Print received bytes
    if (offset > 0) {
        Serial.print(label);
        Serial.print(" Response: ");
        for (size_t i = 0; i < offset; i++) {
            Serial.print("0x");
            Serial.print(buf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }

    return offset;
}

unsigned int CRC16_2(unsigned char *buf, int len) {
    unsigned int crc = 0xFFFF;
    for (int pos = 0; pos < len; pos++) {
        crc ^= (unsigned int)buf[pos];
        for (int i = 8; i != 0; i--) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}*/

saveJsonToFile();
