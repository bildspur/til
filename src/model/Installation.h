#ifndef TIL_INSTALLATION_H
#define TIL_INSTALLATION_H

#include <EEPROM.h>
#include <assert.h>
#include "Luboid.h"

#define EEPROM_SIZE 0x80
#define EEPROM_SIZE_ADDR 0x00
#define EEPROM_DATA_ADDR 0x02

typedef Luboid *LuboidPtr;

class Installation {
private:
    LuboidPtr *lubiods;

    uint16_t size;

public:
    Installation(uint16_t size, LuboidPtr *luboids);

    uint16_t getSize();

    LuboidPtr *getLuboids();

    LuboidPtr getLuboid(uint16_t index);

    LuboidPtr getLuboid(int index);

    void initLuboids();

    void turnOn();

    void turnOff();
};


#endif //TIL_INSTALLATION_H
