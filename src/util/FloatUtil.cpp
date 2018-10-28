//
// Created by Florian on 06.12.17.
//

#include <Arduino.h>
#include "FloatUtil.h"
#include "../model/Luboid.h"

FloatUtil::FloatUtil() = default;

float FloatUtil::map(float value, float minIn, float maxIn, float minOut, float maxOut) {
    return (value - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

float FloatUtil::limit(float value, float min, float max) {
    return (value < max ? value : max) > min ? value : min;
}

float FloatUtil::windowedSine(float x) {
    if (x < 0.0f || x > 1.0f)
        return 0.0f;

    // calculate sine
    return static_cast<float>(0.5 * (1 + sin(2 * PI * x - (PI / 2))));
}

bool FloatUtil::isRandomCalled(float factor) {
    return (random(0, 1000) / 1000.0) > factor;
}

float FloatUtil::mapFromLEDBrightness(float value, float minValue, float maxValue) {
    return FloatUtil::map(value, LUBOID_MIN_BRIGHTNESS, LUBOID_MAX_BRIGHTNESS, minValue, maxValue);
}

float FloatUtil::millisToSeconds(float millis) {
    return millis / 1000;
}

float FloatUtil::secondsToMillis(float seconds) {
    return seconds * 1000;
}
