
#define INF 2000000000
#define LED 13
#define SENSOR A0

int sensorVal = 0;
int sensorMin = INF;
int sensorMax = -INF;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);
  digitalWrite(LED, HIGH);

  Serial.begin(9600);
  while (millis() < 5000) {
    sensorVal = analogRead(SENSOR);
    sensorMax = max(sensorMax, sensorVal);
    sensorMin = min(sensorMin, sensorVal);
  }

  sensorMin -= 5; sensorMax += 5; //error buffer
  Serial.print(sensorMin + " " + sensorMax);
  digitalWrite(LED, LOW);
}

void loop() {
  sensorVal = analogRead(SENSOR);
  Serial.println(sensorVal);
  delay(0);

  sensorVal = map(sensorVal, sensorMin, sensorMax, 0, 255);
  sensorVal = constrain(sensorVal, 0, 255);
  analogWrite(LED, sensorVal);
}
