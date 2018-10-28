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

void Installation::loadFromEEPROM() {
    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("failed to initialise EEPROM");
        return;
    }

    // set start address
    int address = EEPROM_START_ADDRESS;

    // global
    minBrightness = EEPROM.readFloat(address);
    address += sizeof(float);

    maxBrightness = EEPROM.readFloat(address);
    address += sizeof(float);

    // time star pattern
    timeStarMinDuration = EEPROM.readULong(address);
    address += sizeof(unsigned long);

    timeStarMaxDuration = EEPROM.readULong(address);
    address += sizeof(unsigned long);

    timeStarRandomOnFactor = EEPROM.readFloat(address);
    address += sizeof(float);

    timeStarMinBrightness = EEPROM.readFloat(address);
    address += sizeof(float);

    timeStarMaxBrightness = EEPROM.readFloat(address);
    address += sizeof(float);

    // wave
    waveDuration = EEPROM.readULong(address);
    address += sizeof(unsigned long);

    waveTravelSpeed = EEPROM.readULong(address);
    address += sizeof(unsigned long);

    waveMinBrightness = EEPROM.readFloat(address);
    address += sizeof(float);

    waveMaxBrightness = EEPROM.readFloat(address);

    // end
    EEPROM.end();
}

void Installation::saveToEEPROM() {
    if (!EEPROM.begin(EEPROM_SIZE)) {
        Serial.println("failed to initialise EEPROM");
        return;
    }

    // set start address
    int address = EEPROM_START_ADDRESS;

    // global
    EEPROM.writeFloat(address, minBrightness);
    address += sizeof(float);

    EEPROM.writeFloat(address, maxBrightness);
    address += sizeof(float);

    // time star pattern
    EEPROM.writeULong(address, timeStarMinDuration);
    address += sizeof(unsigned long);

    EEPROM.writeULong(address, timeStarMaxDuration);
    address += sizeof(unsigned long);

    EEPROM.writeFloat(address, timeStarRandomOnFactor);
    address += sizeof(float);

    EEPROM.writeFloat(address, timeStarMinBrightness);
    address += sizeof(float);

    EEPROM.writeFloat(address, timeStarMaxBrightness);
    address += sizeof(float);

    // wave
    EEPROM.writeULong(address, waveDuration);
    address += sizeof(unsigned long);

    EEPROM.writeULong(address, waveTravelSpeed);
    address += sizeof(unsigned long);

    EEPROM.writeFloat(address, waveMinBrightness);
    address += sizeof(float);

    EEPROM.writeFloat(address, waveMaxBrightness);

    // save
    EEPROM.commit();
    EEPROM.end();
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
