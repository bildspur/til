//
// Created by Florian Bruggisser on 22.10.18.
//

#include "SerialMotionSensor.h"

HardwareSerial SerialSM(2);

SerialMotionSensor::SerialMotionSensor(uint8_t rxPin, unsigned long baud, unsigned int updateFrequency) : MotionSensor(
        updateFrequency) {
    this->rxPin = rxPin;
    this->baud = baud;
}

void SerialMotionSensor::setup() {
    MotionSensor::setup();

    // setup serial
    SerialSM.begin(baud, SERIAL_8N1, 12, -1, false);
}

void SerialMotionSensor::measure() {
    MotionSensor::measure();

    // check rx pin
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

    // process input
    if (inputString.startsWith("t")) {
        // move, example: "t:r"
        inputString.remove(0, 2);
        auto dir = inputString;

        if (dir.startsWith("r")) {
            // movement from right to left -> set flag
            this->motionDetected = true;
        }
    }
}
