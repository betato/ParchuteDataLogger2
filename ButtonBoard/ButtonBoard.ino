#define BTN_1 3
#define BTN_2 2
#define BTN_3 7
#define BTN_4 8

#define LED_1 5
#define LED_2 6
#define LED_3 9
#define LED_4 10

void setup() {
  commInit();
  
  pinMode(BTN_1, INPUT);
  pinMode(BTN_2, INPUT);
  pinMode(BTN_3, INPUT);
  pinMode(BTN_4, INPUT);
  attachInterrupt(digitalPinToInterrupt(BTN_1), press, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BTN_2), press, CHANGE);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  
}

void loop() {
  if (digitalRead(BTN_4)) {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    checkConnections();
    delay(1000);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
  }
}

void press() {
  //digitalWrite(LED_1, digitalRead(BTN_1));
  //digitalWrite(LED_2, digitalRead(BTN_2));
}
