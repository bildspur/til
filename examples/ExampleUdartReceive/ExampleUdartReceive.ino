#include <SoftwareSerial.h>

#define LED_PIN D6
#define BAUD_RATE 115200

SoftwareSerial openMVSerial(D5, D5, false, 256);

String inputString;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  openMVSerial.begin(115200);

  openMVSerial.enableTx(false);

  doBlink();
}

void loop() {
  processSerial();
  delay(10);
}

void doBlink()
{
  digitalWrite(LED_PIN, HIGH);
  delay(50);
  digitalWrite(LED_PIN, LOW);
  delay(50);
}

void processSerial()
{
  inputString = "";
  while (openMVSerial.available()) {
    auto c = static_cast<char>(openMVSerial.read());
    inputString += c;
    delay(2);
  }

  // if no input -> opt out
  if (inputString.length() == 0) {
    return;
  }

  // process input
  if (inputString.startsWith("t"))
  {
    // move, example: "m:r"
    inputString.remove(0, 2);
    auto dir = inputString;

    if (dir.startsWith("r"))
    {
      Serial.println("right");
      doBlink();
      doBlink();
    }
    else
    {
      Serial.println("left");
      doBlink();
    }
  }
}

