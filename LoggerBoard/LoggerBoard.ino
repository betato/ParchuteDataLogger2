void setup() {
  //delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  commInit();
  //initSd();
}

void loop() {
  //commRequest();
  //delay(2000);
  //sdWrite();
  transmit();
}
