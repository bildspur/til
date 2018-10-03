//
// Created by Florian on 15.11.17.
//

#include "Timer.h"

Timer::Timer(unsigned long waitTime) {
    this->waitTime = waitTime;
}

bool Timer::elapsed() {
    unsigned long currentMillis = millis();
    bool result = currentMillis - previousMillis >= waitTime;

    if(result)
        previousMillis = currentMillis;

    return result;
}

void Timer::reset() {
    previousMillis = millis();
}

void Timer::setWaitTime(unsigned long waitTime) {
    Timer::waitTime = waitTime;
}
