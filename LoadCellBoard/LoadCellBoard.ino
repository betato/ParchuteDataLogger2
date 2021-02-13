void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  commInit();
  initScales();
  Serial.begin(9600);
  delay(1000);
  setScalePower(true);
}

//float vertical;
//float axial;
//float horizontal;

void loop() {
  transmit();
  //horizontal = getHorizontal();
}
