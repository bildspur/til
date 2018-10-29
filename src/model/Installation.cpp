//
// Created by Florian on 30.11.17.
//

#include "Installation.h"
#include "../util/MathUtils.h"

Installation::Installation(uint16_t size, LuboidPtr *luboids) {
    this->size = size;
    this->lubiods = luboids;
    this->settings = new AppSettings();
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
    // set start address
    int address = EEPROM_START_ADDRESS;
    EEPROM.get(address, *settings);

    // check version and set default if needed
    if (settings->getVersion() != TIL_SETTINGS_VERSION)
        settings = new AppSettings();
}

void Installation::saveToEEPROM() {
    // set start address
    int address = EEPROM_START_ADDRESS;
    EEPROM.put(address, &settings);
}

AppSettings *Installation::getSettings() const {
    return settings;
}
