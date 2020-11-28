#include <Wire.h>

#define DI2C_EN 4

#define ADDR_BUTTON 6
#define ADDR_LOGGER 7
#define ADDR_LOADCELL 8
#define ADDR_ANEMOMETER 9

#define OP_CHECK 0
#define OP_GOOD 1
#define OP_BAD 2
#define OP_START 2
#define OP_STOP 3

void commInit() {
  // Enable DI2C IC
  pinMode(DI2C_EN, OUTPUT);
  digitalWrite(DI2C_EN, HIGH);
  // Init
  Wire.begin(ADDR_BUTTON);
  Wire.onReceive(received);
}

void checkConnections() {
  digitalWrite(LED_1, HIGH);
  delay(200);
  
  Wire.beginTransmission(ADDR_LOGGER);
  Wire.write(OP_CHECK);
  Wire.endTransmission();
  delay(200);
  
  Wire.beginTransmission(ADDR_LOADCELL);
  Wire.write(OP_CHECK);
  Wire.endTransmission();
  delay(200);
  
  Wire.beginTransmission(ADDR_ANEMOMETER);
  Wire.write(OP_CHECK);
  Wire.endTransmission();
  delay(200);
}

void syncTime() {
  // Synchronize logger and anemometer boards
}

void logPoint() {
  Wire.beginTransmission(ADDR_LOADCELL);
  Wire.write("x is ");
  Wire.endTransmission();
}

void received(int numBytes) {
  digitalWrite(LED_BUILTIN, HIGH);
  // Get opcode
  byte opcode;
  if (Wire.available()) {
    opcode = Wire.read();
  }

  if (opcode == OP_GOOD && Wire.available()) {
    byte module = Wire.read();
    if (module == ADDR_LOGGER){
      digitalWrite(LED_2, HIGH);
    } else if (module == ADDR_LOADCELL){
      digitalWrite(LED_3, HIGH);
    } else if (module == ADDR_ANEMOMETER){
      digitalWrite(LED_4, HIGH);
    }
  }
}
