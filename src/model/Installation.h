#ifndef TIL_INSTALLATION_H
#define TIL_INSTALLATION_H

#include <EEPROM.h>
#include <assert.h>
#include "Luboid.h"
#include "EEPROM.h"

#define EEPROM_SIZE 0x80
#define EEPROM_ 0x00

typedef Luboid *LuboidPtr;

class Installation {
private:
    LuboidPtr *lubiods;

    uint16_t size;

    float minBrightness = 0.0f;

    float maxBrightness = 1.0f;

public:
    Installation(uint16_t size, LuboidPtr *luboids);

    uint16_t getSize();

    LuboidPtr *getLuboids();

    LuboidPtr getLuboid(uint16_t index);

    LuboidPtr getLuboid(int index);

    void initLuboids();

    void loadFromEEPROM();

    void saveToEEPROM();

    void turnOn();

    void turnOff();

    float getMinBrightness() const;

    void setMinBrightness(float ledMinBrightness);

    float getMaxBrightness() const;

    void setMaxBrightness(float ledMaxBrightness);
};


#endif //TIL_INSTALLATION_H
