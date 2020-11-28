void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  commInit();
  initScales();
}

void loop() {
  transmit();
}
