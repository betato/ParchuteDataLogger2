#include <Wire.h>

#define DI2C_EN 4

#define ADDR_BUTTON 6
#define ADDR_LOGGER 7
#define ADDR_LOADCELL 8
#define ADDR_ANEMOMETER 9

#define OP_CHECK 0
#define OP_CHECK_RESPONSE 1
#define OP_START 2
#define OP_STOP 3

void commInit() {
  // Enable DI2C IC
  pinMode(DI2C_EN, OUTPUT);
  digitalWrite(DI2C_EN, HIGH);
  // Init
  Wire.begin(ADDR_LOADCELL);
  Wire.onReceive(received);
}

void received(int numBytes) {
  byte opcode;
  if (Wire.available()) {
    opcode = Wire.read();
  }

  // Send check response
  if (opcode == OP_CHECK) {
    digitalWrite(LED_BUILTIN, HIGH);
    Wire.beginTransmission(ADDR_BUTTON);
    Wire.write((byte)OP_CHECK_RESPONSE);
    Wire.write((byte)ADDR_LOADCELL);
    Wire.endTransmission();
  }
}
