#include <Wire.h>

#define DI2C_EN 4

#define ADDR_BUTTON 6
#define ADDR_LOGGER 7
#define ADDR_LOADCELL 8
#define ADDR_ANEMOMETER 9

#define OP_CHECK 0
#define OP_GOOD 1
#define OP_BAD 2
#define OP_START 3
#define OP_STOP 4

void commInit() {
  // Enable DI2C IC
  pinMode(DI2C_EN, OUTPUT);
  digitalWrite(DI2C_EN, HIGH);
  // Init
  Wire.begin(ADDR_LOGGER);
  Wire.onReceive(received);
}

bool sendCheckResponse = false;
void transmit() {
  if (sendCheckResponse) {
    digitalWrite(LED_BUILTIN, HIGH);
    Wire.beginTransmission(ADDR_BUTTON);
    Wire.write(OP_GOOD);
    Wire.write(ADDR_LOGGER);
    Wire.endTransmission();
    sendCheckResponse = false;
  }
}


void received(int numBytes) {
  byte opcode;
  if (Wire.available()) {
    opcode = Wire.read();
  }

  // Send check response
  if (opcode == OP_CHECK)
    sendCheckResponse = true;

  if (opcode == OP_START)
    sendCheckResponse = true;
}
