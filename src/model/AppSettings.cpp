//
// Created by Florian Bruggisser on 29.10.18.
//

#include "AppSettings.h"

float AppSettings::getMinBrightness() const {
    return minBrightness;
}

void AppSettings::setMinBrightness(float minBrightness) {
    AppSettings::minBrightness = minBrightness;
}

float AppSettings::getMaxBrightness() const {
    return maxBrightness;
}

void AppSettings::setMaxBrightness(float maxBrightness) {
    AppSettings::maxBrightness = maxBrightness;
}

unsigned long AppSettings::getTimeStarMinDuration() const {
    return timeStarMinDuration;
}

void AppSettings::setTimeStarMinDuration(unsigned long timeStarMinDuration) {
    AppSettings::timeStarMinDuration = timeStarMinDuration;
}

unsigned long AppSettings::getTimeStarMaxDuration() const {
    return timeStarMaxDuration;
}

void AppSettings::setTimeStarMaxDuration(unsigned long timeStarMaxDuration) {
    AppSettings::timeStarMaxDuration = timeStarMaxDuration;
}

float AppSettings::getTimeStarRandomOnFactor() const {
    return timeStarRandomOnFactor;
}

void AppSettings::setTimeStarRandomOnFactor(float timeStarRandomOnFactor) {
    AppSettings::timeStarRandomOnFactor = timeStarRandomOnFactor;
}

float AppSettings::getTimeStarMinBrightness() const {
    return timeStarMinBrightness;
}

void AppSettings::setTimeStarMinBrightness(float timeStarMinBrightness) {
    AppSettings::timeStarMinBrightness = timeStarMinBrightness;
}

float AppSettings::getTimeStarMaxBrightness() const {
    return timeStarMaxBrightness;
}

void AppSettings::setTimeStarMaxBrightness(float timeStarMaxBrightness) {
    AppSettings::timeStarMaxBrightness = timeStarMaxBrightness;
}

unsigned long AppSettings::getWaveDuration() const {
    return waveDuration;
}

void AppSettings::setWaveDuration(unsigned long waveDuration) {
    AppSettings::waveDuration = waveDuration;
}

unsigned long AppSettings::getWaveTravelSpeed() const {
    return waveTravelSpeed;
}

void AppSettings::setWaveTravelSpeed(unsigned long waveTravelSpeed) {
    AppSettings::waveTravelSpeed = waveTravelSpeed;
}

float AppSettings::getWaveMinBrightness() const {
    return waveMinBrightness;
}

void AppSettings::setWaveMinBrightness(float waveMinBrightness) {
    AppSettings::waveMinBrightness = waveMinBrightness;
}

float AppSettings::getWaveMaxBrightness() const {
    return waveMaxBrightness;
}

void AppSettings::setWaveMaxBrightness(float waveMaxBrightness) {
    AppSettings::waveMaxBrightness = waveMaxBrightness;
}

int AppSettings::getVersion() const {
    return version;
}
