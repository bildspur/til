//
// Created by Florian Bruggisser on 25.10.18.
//

#include "TimeStar.h"
#include "../../../util/MathUtils.h"

TimeStar::TimeStar() {

}

bool TimeStar::isRunning(unsigned long timeStamp) {
    return timeStamp - startTime < duration;
}

void TimeStar::start(unsigned long timeStamp, unsigned long duration) {
    startTime = timeStamp;
    this->duration = duration;
}

float TimeStar::getBrightness(unsigned long timeStamp) {
    // calculate normalized time
    auto nvalue = (timeStamp - startTime) / (float) duration;
    return MathUtils::windowedSine(nvalue);
}


