void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(5, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int button = digitalRead(5);
  if (button == 0) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);
}
