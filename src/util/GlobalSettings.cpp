//
// Created by Florian Bruggisser on 25.10.18.
//

#include "GlobalSettings.h"
#include "FloatUtil.h"

float GlobalSettings::ledMinBrightness = 0.0f;
float GlobalSettings::ledMaxBrightness = 1.0f;

void GlobalSettings::load() {

}

void GlobalSettings::save() {

}

float GlobalSettings::getLedMinBrightness() {
    return ledMinBrightness;
}

void GlobalSettings::setLedMinBrightness(float ledMinBrightness) {
    GlobalSettings::ledMinBrightness = ledMinBrightness;
}

float GlobalSettings::getLedMaxBrightness() {
    return ledMaxBrightness;
}

void GlobalSettings::setLedMaxBrightness(float ledMaxBrightness) {
    GlobalSettings::ledMaxBrightness = ledMaxBrightness;
}

float GlobalSettings::clampGlobalBrightness(float value, float minValue, float maxValue) {
    return FloatUtil::map(value, ledMinBrightness, ledMaxBrightness, minValue, maxValue);
}

