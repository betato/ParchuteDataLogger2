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
#define OP_REQUEST 5
#define OP_DATA 6

void commInit() {
  // Enable DI2C IC
  pinMode(DI2C_EN, OUTPUT);
  digitalWrite(DI2C_EN, HIGH);
  // Init
  Wire.setTimeout(400);
  Wire.begin(ADDR_ANEMOMETER);
  Wire.onReceive(received);
}

bool sendCheckResponse = false;
bool sdError = false;

void transmit() {
  if (sendCheckResponse) {
    Wire.beginTransmission(ADDR_BUTTON);
    Wire.write(sdError ? OP_BAD : OP_GOOD);
    Wire.write(ADDR_ANEMOMETER);
    Wire.endTransmission();
    sendCheckResponse = false;
  }
}


void received(int numBytes) {
  digitalWrite(LED_BUILTIN, HIGH);
  
  byte command;
  if (Wire.available()) {
    command = Wire.read();
  }

  // Send check response
  if (command == OP_CHECK)
    sendCheckResponse = true;

  // Sync clocks
  //else if (command == OP_REQUEST)
  
}
