//
// Created by Florian on 06.12.17.
//

#include "FloatUtil.h"

FloatUtil::FloatUtil() = default;

float FloatUtil::map(float value, float minIn, float maxIn, float minOut, float maxOut) {
    return (value - minIn) * (maxOut - minOut) / (maxIn - minIn) + minOut;
}

float FloatUtil::limit(float value, float min, float max) {
    return (value < max ? value : max) > min ? value : min;
}
