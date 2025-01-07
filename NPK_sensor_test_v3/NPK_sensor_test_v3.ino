  #include <ArduinoJson.h>

  #define ARRAY_SIZE 10

  int NArr[ARRAY_SIZE] = {12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
  int PArr[ARRAY_SIZE] = {10, 12, 14, 16, 18, 20, 22, 24, 26, 28};
  int KArr[ARRAY_SIZE] = {5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
  int AArr[ARRAY_SIZE] = {192, 193, 194, 195, 196, 197, 198, 199, 200, 201};
  int RArr[ARRAY_SIZE] = {9600, 9600, 9600, 9600, 9600, 9600, 9600, 9600, 9600, 9600};

  void setup() 
  {

      Serial.begin(9600);    // Debug serial
      while (!Serial) {} // Vent til serial-forbindelsen er klar
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

      delay(10000); // Send data hver 5. sekund
  }
