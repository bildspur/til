//
// Created by Florian on 29.11.17.
//

#include "MotionSensor.h"

MotionSensor::MotionSensor(unsigned int updateFrequency) {
    timer = new Timer(updateFrequency);
}

void MotionSensor::setup() {
    BaseController::setup();
}

void MotionSensor::loop() {
    BaseController::loop();

    // read value
    if (timer->elapsed()) {
        measure();
    }
}

bool MotionSensor::isMotionDetected(bool clearFlag) {
    bool value = motionDetected;

    // clear value if requested
    if (clearFlag)
        motionDetected = false;

    return value;
}

void MotionSensor::measure() {

}
