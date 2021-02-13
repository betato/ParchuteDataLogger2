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
  Wire.begin(ADDR_LOADCELL);
  Wire.onReceive(received);
}

bool sendCheckResponse = false;
bool transmitNow = false;
union floatToBytes {
    char c[4];
    float f;
} converter;
  
void transmit() {
  if (sendCheckResponse) {
    Wire.beginTransmission(ADDR_BUTTON);
    Wire.write(scalesReady() ? OP_GOOD : OP_BAD);
    Wire.write(ADDR_LOADCELL);
    Wire.endTransmission();
    sendCheckResponse = false;
  } else if (transmitNow) {
    Wire.beginTransmission(ADDR_LOGGER);
    Wire.write(OP_DATA);
    converter.f = getVertical();
    Wire.write(converter.c);
    delay(100);
    converter.f = getAxial();
    Wire.write(converter.c);
    delay(100);
    converter.f = getHorizontal();
    Wire.write(converter.c);
    Wire.endTransmission();
    transmitNow = false;
  }
}


void received(int numBytes) {
  byte command;
  if (Wire.available()) {
    command = Wire.read();
  }

  // Send check response
  if (command == OP_CHECK) {
    sendCheckResponse = true;

  // Power scales on/off
  } else if (command == OP_START) {
    setScalePower(true);
  } else if (command == OP_STOP) {
    setScalePower(false);

  // Send data to logger board
  } else if (command == OP_REQUEST) {
    transmitNow = true;
  }
}
