//
// Created by Florian Bruggisser on 23.10.18.
//

#include <esp32-hal.h>
#include "StopWatch.h"

StopWatch::StopWatch() = default;

void StopWatch::start() {
    running = true;
    startTime = millis();
}

void StopWatch::stop() {
    running = false;
    stopTime = millis();
}

unsigned long StopWatch::elapsed() {
    if (running)
        return millis() - startTime;

    return stopTime - startTime;
}
