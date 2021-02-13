#define LOG_INTERVAL 1000

#define ANGLE_PIN A0
#define VELOCITY_PIN A1

bool logging = false;
unsigned long nextLog;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  commInit();
  nextLog = millis() + LOG_INTERVAL;
}

void loop() {
  transmit();
  if (logging && nextLog <= millis()) {
    logData(getAngle(), getVelocity());
    nextLog += LOG_INTERVAL;
  }
}

float getAngle() {
  return analogRead(ANGLE_PIN);
}

float getVelocity() {
  return analogRead(VELOCITY_PIN);
}



    
