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
  Wire.begin(ADDR_LOGGER);
  Wire.onReceive(received);
}

bool sdError = false;
bool sendCheckResponse = false;

void transmit() {
  if (sendCheckResponse) {
    Wire.beginTransmission(ADDR_BUTTON);
    Wire.write(sdError ? OP_BAD : OP_GOOD);
    Wire.write(ADDR_LOGGER);
    Wire.endTransmission();
    sendCheckResponse = false;
  }
}

void sendLogEvent() {
  Wire.beginTransmission(ADDR_BUTTON);
  Wire.write(OP_DATA);
  Wire.endTransmission();
}

void received(int numBytes) {
  byte command;
  if (Wire.available()) {
    command = Wire.read();
  }

  // Send check response
  if (command == OP_CHECK) {
    sendCheckResponse = true;
  } else if (command == OP_START) {
    logging = true;
    newFile();
    
  } else if (command == OP_STOP) {
    logging = false;
    
  } else if (command == OP_DATA) {
    // Load cell data recieved
    logData[logCount][0] = millis()/1000.0;
    logData[logCount][1] = getVelocity();
    logData[logCount][2] = wireReadFloat();
    logData[logCount][3] = wireReadFloat();
    logData[logCount][3] = wireReadFloat();
    
    logRecieved = true;
  }
}

union floatToBytes {
    char c[4];
    float f;
} converter;

float wireReadFloat() {
  int i = 0;
  while (Wire.available()) {
    converter.c[i++] = Wire.read();
  }
  return converter.f;
}
