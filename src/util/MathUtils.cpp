//
// Created by Florian on 06.12.17.
//

#include <Arduino.h>
#include "MathUtils.h"
#include "../model/Luboid.h"

MathUtils::MathUtils() = default;

float MathUtils::map(float value, float minIn, float maxIn, float minOut, float maxOut) {
    return (value - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

float MathUtils::limit(float value, float min, float max) {
    return (value < max ? value : max) > min ? value : min;
}

float MathUtils::windowedSine(float x) {
    if (x < 0.0f || x > 1.0f)
        return 0.0f;

    // calculate sine
    return static_cast<float>(0.5 * (1 + sin(2 * PI * x - (PI / 2))));
}

bool MathUtils::isRandomCalled(float factor) {
    return (random(0, 1000) / 1000.0) > factor;
}

float MathUtils::mapFromLEDBrightness(float value, float minValue, float maxValue) {
    return MathUtils::map(value, LUBOID_MIN_BRIGHTNESS, LUBOID_MAX_BRIGHTNESS, minValue, maxValue);
}

unsigned long MathUtils::millisToSeconds(unsigned long millis) {
    return millis / 1000;
}

unsigned long MathUtils::secondsToMillis(unsigned long seconds) {
    return seconds * 1000;
}
