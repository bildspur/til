//
// Created by Florian on 27.11.17.
//

#include <HardwareSerial.h>
#include "Luboid.h"

Luboid::Luboid(uint8_t id, uint8_t distance) {
    this->id = id;
}

void Luboid::update() {
    brightness.update();
}

void Luboid::setBrightness(float value, bool easing) {
    if (easing)
        brightness.setTarget(value);
    else
        brightness.set(value);
}

float Luboid::getBrightness() {
    return brightness.get();
}

uint8_t Luboid::getId() {
    return id;
}

void Luboid::turnOn(bool easing) {
    setBrightness(LUBOID_MAX_BRIGHTNESS, easing);
}

void Luboid::turnOff(bool easing) {
    setBrightness(LUBOID_MIN_BRIGHTNESS, easing);
}
