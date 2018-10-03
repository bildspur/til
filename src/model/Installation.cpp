//
// Created by Florian on 30.11.17.
//

#include "Installation.h"

Installation::Installation(uint16_t size, LuboidPtr *luboids) {
    this->size = size;
    this->leafs = luboids;
}

uint16_t Installation::getSize() {
    return size;
}

LuboidPtr *Installation::getLuboids() {
    return leafs;
}

LuboidPtr Installation::getLuboid(uint16_t index) {
    assert(index >= 0 && index < size);
    return leafs[index];
}

LuboidPtr Installation::getLuboid(int index) {
    return getLuboid(static_cast<uint16_t>(index));
}

void Installation::loadLuboids() {
    initLuboids();

    // setup eeprom
    EEPROM.begin(EEPROM_SIZE);

    // load from eeprom check size and create
    uint16_t storedSize = 0;
    EEPROM.get(EEPROM_SIZE_ADDR, storedSize);

    // if size does not match reinit
    if(storedSize != size)
        return;

    // read distance and set it to leafs
    for(auto i = 0; i < size; i++)
    {
        uint8_t distance = 0;
        EEPROM.get(EEPROM_DATA_ADDR + i, distance);
        leafs[i]->setDistance(distance);
    }

    EEPROM.end();
}

void Installation::saveLuboids() {
    EEPROM.begin(EEPROM_SIZE);

    // save size
    EEPROM.put(EEPROM_SIZE_ADDR, size);

    // save leaf distances
    for(auto i = 0; i < size; i++)
    {
        EEPROM.put(EEPROM_DATA_ADDR + i, leafs[i]->getDistance());
    }

    EEPROM.end();
}

void Installation::initLuboids() {
    for (uint8_t i = 0; i < size; i++) {
        leafs[i] = new Luboid(i);
    }
}
