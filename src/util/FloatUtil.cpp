//
// Created by Florian on 06.12.17.
//

#include <Arduino.h>
#include "FloatUtil.h"

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
