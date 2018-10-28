// - - - - -
// ESPDMX - A Arduino library for sending and receiving DMX using the builtin serial hardware port.
//
// Copyright (C) 2015  Rick <ricardogg95@gmail.com>
// This work is licensed under a GNU style license.
//
// Last change: Musti <https://github.com/IRNAS> (edited by Musti)
//
// Documentation and samples are available at https://github.com/Rickgg/ESP-Dmx
// Connect GPIO02 - TDX1 to MAX3485 or other driver chip to interface devices
// Pin is defined in library
// - - - - -

#include <ESPDMX.h>

DMXESPSerial dmx;

void setup() {
  Serial.begin(115200);

  delay(3000);

  Serial.println("starting...");

  dmx.init(512, 2);           // initialization for complete bus

  Serial.println("initialized...");
  delay(200);               // wait a while (not necessary)

  //fadeDmx(true, 10);
  setDmx(0);

  Serial.println("finished!");

  delay(5000);
}

void writeController(int channel, int value)
{
  for (int i = 0; i < 4; i++)
    dmx.write((channel * 4) + i, value);
  dmx.update();
}

void loop() {
  // turn slowly on

  //fadeDmx(true, 5);

  //delay(500);

  // turn slowly off
  //fadeDmx(false, 5);

  //delay(1000);

  setDmx(0);
  delay(5);

  int intensity = 255;

  for (int i = 0; i < 33; i++)
  {
    Serial.print("Lighting up luboid ");
    Serial.println(i);

    fadeDmxSensible(true, i, 1, intensity, 85);
  }

  delay(5000);

  for (int i = 0; i < 33; i++)
  {
    Serial.print("Turing off luboid ");
    Serial.println(i);

    fadeDmxSensible(false, i, 1, intensity, 85);
  }

  setDmx(0);
  delay(1000);
}

void singleLightUp(int luboidId, int value)
{
  setDmx(0);

  writeController(luboidId, value);
}

void blinkLeds(int times, int delayTime)
{
  for (int i = 0; i < times; i++)
  {
    setDmx(0);
    delay(delayTime);
    setDmx(255);
    delay(delayTime);
  }
}

void fadeBlink(int times, int delayTime, int fadeTime)
{
  for (int i = 0; i < times; i++)
  {
    fadeDmx(false, fadeTime);
    delay(delayTime);
    fadeDmx(true, fadeTime);
    delay(delayTime);
  }
}

void fadeDmxSensible(boolean turnOn, int luboidId, int fadeSpeed, int maxLight, int nspeed)
{
  for (int i = 0; i < maxLight; i += nspeed)
  {
    if (turnOn)
    {
      writeController(luboidId, i);
    }
    else
    {
      writeController(luboidId, maxLight - i);
    }

    delay(fadeSpeed);
  }
}

void fadeDmx(boolean turnOn, int fadeSpeed)
{
  for (int i = 0; i < 256; i++)
  {
    if (turnOn)
    {
      setDmx(i);
    }
    else
    {
      setDmx(255 - i);
    }

    delay(fadeSpeed);
  }
}

void setDmx(int value)
{
  for (int i = 0; i < 512; i++)
  {
    dmx.write(i, value);
  }
  dmx.update();
}
