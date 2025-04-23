#include <SoftwareSerial.h>

// GPS module connected to D4 (RX), D3 (TX - optional)
SoftwareSerial gpsSerial(4, 3);  // RX, TX

String line = "";

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Serial.println("Reading NMEA sentences from GPS...");
}

void loop() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    line += c;

    if (c == '\n') {
      // Uncomment below to print all NMEA sentences
      // Serial.print(line);

      // Only print GPGSV (satellite info)
      if (line.startsWith("$GPGSV")) {
        Serial.print("Satellites Info: ");
        Serial.print(line);
      }

      line = "";
    }
  }
}