//
// Created by Florian on 30.11.17.
//

#include "Installation.h"
#include "../util/MathUtils.h"

Installation::Installation(uint16_t size, LuboidPtr *luboids) {
    this->size = size;
    this->lubiods = luboids;
}

uint16_t Installation::getSize() {
    return size;
}

LuboidPtr *Installation::getLuboids() {
    return lubiods;
}

LuboidPtr Installation::getLuboid(uint16_t index) {
    assert(index >= 0 && index < size);
    return lubiods[index];
}

LuboidPtr Installation::getLuboid(int index) {
    return getLuboid(static_cast<uint16_t>(index));
}

void Installation::initLuboids() {
    for (uint8_t i = 0; i < size; i++) {
        lubiods[i] = new Luboid(i);
    }
}

void Installation::turnOn() {
    for (auto i = 0; i < size; i++) {
        lubiods[i]->turnOn();
    }
}

void Installation::turnOff() {
    for (auto i = 0; i < size; i++) {
        lubiods[i]->turnOff();
    }
}

float Installation::getMinBrightness() const {
    return minBrightness;
}

void Installation::setMinBrightness(float ledMinBrightness) {
    Installation::minBrightness = ledMinBrightness;
}

float Installation::getMaxBrightness() const {
    return maxBrightness;
}

void Installation::setMaxBrightness(float ledMaxBrightness) {
    Installation::maxBrightness = ledMaxBrightness;
}

void Installation::loadFromEEPROM() {

}

void Installation::saveToEEPROM() {

}

unsigned long Installation::getTimeStarMinDuration() const {
    return timeStarMinDuration;
}

void Installation::setTimeStarMinDuration(unsigned long timeStarMinDuration) {
    Installation::timeStarMinDuration = timeStarMinDuration;
}

unsigned long Installation::getTimeStarMaxDuration() const {
    return timeStarMaxDuration;
}

void Installation::setTimeStarMaxDuration(unsigned long timeStarMaxDuration) {
    Installation::timeStarMaxDuration = timeStarMaxDuration;
}

float Installation::getTimeStarRandomOnFactor() const {
    return timeStarRandomOnFactor;
}

void Installation::setTimeStarRandomOnFactor(float timeStarRandomOnFactor) {
    Installation::timeStarRandomOnFactor = timeStarRandomOnFactor;
}

float Installation::getTimeStarMinBrightness() const {
    return timeStarMinBrightness;
}

void Installation::setTimeStarMinBrightness(float timeStarMinBrightness) {
    Installation::timeStarMinBrightness = timeStarMinBrightness;
}

float Installation::getTimeStarMaxBrightness() const {
    return timeStarMaxBrightness;
}

void Installation::setTimeStarMaxBrightness(float timeStarMaxBrightness) {
    Installation::timeStarMaxBrightness = timeStarMaxBrightness;
}

unsigned long Installation::getWaveDuration() const {
    return waveDuration;
}

void Installation::setWaveDuration(unsigned long waveTime) {
    Installation::waveDuration = waveTime;
}

unsigned long Installation::getWaveTravelSpeed() const {
    return waveTravelSpeed;
}

void Installation::setWaveTravelSpeed(unsigned long waveTravelSpeed) {
    Installation::waveTravelSpeed = waveTravelSpeed;
}

float Installation::getWaveMinBrightness() const {
    return waveMinBrightness;
}

void Installation::setWaveMinBrightness(float waveMinBrightness) {
    Installation::waveMinBrightness = waveMinBrightness;
}

float Installation::getWaveMaxBrightness() const {
    return waveMaxBrightness;
}

void Installation::setWaveMaxBrightness(float waveMaxBrightness) {
    Installation::waveMaxBrightness = waveMaxBrightness;
}
