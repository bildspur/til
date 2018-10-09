#define LED_PIN 2

int i = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  doBlink();
}

void loop() {
  Serial.print("test: ");
  Serial.println(i);

  i++;
  delay(500);
}

void doBlink()
{
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}
