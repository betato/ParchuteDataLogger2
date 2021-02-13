#define LINES_PER_WRITE 4
float logData[LINES_PER_WRITE][5]; // Time, Velocity, Vertical, Axial, Horizontal
int logCount = 0;

void setup() {
  // Hall sensor
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), speedometerTick, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), speedometerTick, FALLING);
  Serial.begin(9600);
  
  commInit();
  initSd();
}

bool logging = false;
bool logRecieved = false;

void loop() {
  transmit();
  
  if (logging && logRecieved) {
    logRecieved = false;
    
    Serial.print(logData[logCount][0], 3);
    Serial.print(", ");
    Serial.print(logData[logCount][1], 2);
    Serial.print(", ");
    Serial.print(logData[logCount][2], 2);
    Serial.print(", ");
    Serial.print(logData[logCount][3], 2);
    Serial.print(", ");
    Serial.println(logData[logCount][4], 2);
    
    logCount++;
    if (logCount >= LINES_PER_WRITE) {
      sdWrite(logData, LINES_PER_WRITE);
      Serial.println("Data logged to SD card");
      logCount = 0;
    }
    sendLogEvent();
  }
}
