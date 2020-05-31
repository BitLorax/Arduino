int lightState = 1;
int prevState = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(9);
  if (buttonState != prevState) {
    if (buttonState == HIGH) {
      lightState *= -1;
    }
    delay(50);
  }
  if (lightState > 0) {
    digitalWrite(10, LOW);
  } else {
    digitalWrite(10, HIGH);
  }
  prevState = buttonState;
}
