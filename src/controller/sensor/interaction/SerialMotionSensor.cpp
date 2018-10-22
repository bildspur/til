//
// Created by Florian Bruggisser on 22.10.18.
//

#include "SerialMotionSensor.h"

SerialMotionSensor::SerialMotionSensor(uint8_t rxPin, unsigned int updateFrequency) : MotionSensor(updateFrequency) {
    this->rxPin = rxPin;
}

void SerialMotionSensor::measure() {
    MotionSensor::measure();

    // check rx pin
    // implement tx reading and measuring!
}
