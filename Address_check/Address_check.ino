#include <Wire.h>
void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("\nI2C Scanner");

  for (byte address = 1; address < 128; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();  
  
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  Serial.println("Scan complete.");
}
void loop() {
}
