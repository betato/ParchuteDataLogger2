void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  commInit();
  initSd();
}

bool logging = false;

void loop() {
  transmit();
  digitalWrite(LED_BUILTIN, logging);
  if (logging) {
    // Write to log
    //sdWrite();
  }
}
