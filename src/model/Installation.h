#ifndef TIL_INSTALLATION_H
#define TIL_INSTALLATION_H

#include <EEPROM.h>
#include <assert.h>
#include "Luboid.h"
#include "EEPROM.h"
#include "AppSettings.h"

#define EEPROM_SIZE 0xFF
#define EEPROM_START_ADDRESS 0x00

typedef Luboid *LuboidPtr;

class Installation {
private:
    LuboidPtr *lubiods;

    uint16_t size;

    AppSettings settings;

public:
    Installation(uint16_t size, LuboidPtr *luboids);

    uint16_t getSize();

    LuboidPtr *getLuboids();

    LuboidPtr getLuboid(uint16_t index);

    LuboidPtr getLuboid(int index);

    void initLuboids();

    void loadFromEEPROM();

    void saveToEEPROM();

    void loadDefaultSettings();

    void turnOn();

    void turnOff();

    AppSettings &getSettings();
};


#endif //TIL_INSTALLATION_H
