#define LED_BUILTIN 17

void setup() {
  // Set pin mode
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  delay(250);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN,LOW);
}
