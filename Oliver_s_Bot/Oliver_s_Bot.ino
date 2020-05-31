int powerLevel = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(5, powerLevel);
  powerLevel++;
  if (powerLevel > 255) {
    powerLevel = 0;
  }
  digitalWrite(6, LOW);
  delay(10);
}
