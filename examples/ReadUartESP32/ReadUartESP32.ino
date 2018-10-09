#define LED_PIN 2

int i = 0;
String inputString;

HardwareSerial SerialSM(1);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  // openmv serial
  SerialSM.begin(9600, SERIAL_8N1, 12, -1, false);

  doBlink();
}

void loop() {
  /*
  Serial.print("test: ");
  Serial.println(i);

  i++;
  */
  delay(100);

  processSerial();
}

void doBlink()
{
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}

void processSerial()
{
  inputString = "";
  while (SerialSM.available()) {
    auto c = static_cast<char>(SerialSM.read());
    inputString += c;
    delay(2);
  }

  // if no input -> opt out
  if (inputString.length() == 0) {
    return;
  }

  Serial.print("data available: ");
  Serial.println(inputString);

  // process input
  if (inputString.startsWith("t"))
  {
    // move, example: "t:r"
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
