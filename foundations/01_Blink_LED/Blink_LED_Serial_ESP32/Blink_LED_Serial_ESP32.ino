#define PIN1 18
#define PIN2 19

void setup() {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
}

void loop() {

  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, LOW);
  delay(500);

  digitalWrite(PIN1, LOW);
  digitalWrite(PIN2, HIGH);
  delay(500);
}

