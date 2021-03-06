#include <SPI.h>
#include <SD.h>

#define CHIP_SELECT 4
#define SD_SW 7

void initSd() {
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(SD_SW, INPUT_PULLUP);
  if (digitalRead(SD_SW) == HIGH) {
    Serial.println("Missing SD card");
    sdError = true;
  }
  
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card initialization failed");
    sdError = true;
  }
  Serial.println("SD card initialized");
}

String fileName = "";
int fileCount = 0;

void newFile() {
  while (SD.exists(getFileName(fileCount))) {
    fileCount++;
  }
  fileName = getFileName(fileCount);
  File logFile = SD.open(fileName, FILE_WRITE);
  if (logFile) {
    Serial.println("New file created");
  } else {
    Serial.println("Error creating file");
    sdError = true;
  }
}

String getFileName(int i){
  return "LOG_" + String(fileCount) + ".CSV";
}

void sdWrite(float data[][5], int len) {
  File logFile = SD.open(fileName, FILE_WRITE);
  if (logFile) {
    for (int i = 0; i < len; i++) {
      logFile.print(data[i][0], 3);   // Time
      logFile.print(", ");
      logFile.print(data[i][1], 2);   // Velocity
      logFile.print(", ");
      logFile.print(data[i][2], 2);   // Vertical
      logFile.print(", ");
      logFile.print(data[i][3], 2);   // Axial
      logFile.print(", ");
      logFile.println(data[i][4], 2); // Horizontal
    }
    logFile.close();
  } else {
    Serial.println("Error opening file");
    sdError = true;
  }
}
