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
    stopForError();
  }
  
  if (!SD.begin(CHIP_SELECT)) {
    Serial.println("Card initialization failed");
    stopForError();
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
  if (!logFile) {
    Serial.println("Error creating file");
    stopForError();
  }
}

String getFileName(int i){
  return "LOG_" + String(fileCount) + ".CSV";
}

void sdWrite() {
  File logFile = SD.open(fileName, FILE_WRITE);
  if (logFile) {
    logFile.print("POTATO");
    logFile.close();
  } else {
    Serial.println("Error opening file");
    stopForError();
  }
}

void stopForError() {
  while(1) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
}
