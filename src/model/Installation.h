#ifndef TIL_INSTALLATION_H
#define TIL_INSTALLATION_H

#include <EEPROM.h>
#include <assert.h>
#include "Luboid.h"
#include "EEPROM.h"

#define EEPROM_SIZE 0x80
#define EEPROM_START_ADDRESS 0x00

typedef Luboid *LuboidPtr;

class Installation {
private:
    LuboidPtr *lubiods;

    uint16_t size;

    // global settings
    float minBrightness = 0.0f;

    float maxBrightness = 1.0f;

    // time star scene settings
    unsigned long timeStarMinDuration = 10000L;

    unsigned long timeStarMaxDuration = 50000L;

    float timeStarRandomOnFactor = 0.99f;

    float timeStarMinBrightness = 0.0f;

    float timeStarMaxBrightness = 0.2f;

    // wave settings
    unsigned long waveDuration = 3000L;

    unsigned long waveTravelSpeed = 500L;

    float waveMinBrightness = 0.0f;

    float waveMaxBrightness = 0.2f;

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

    unsigned long getTimeStarMinDuration() const;

    void setTimeStarMinDuration(unsigned long timeStarMinDuration);

    unsigned long getTimeStarMaxDuration() const;

    void setTimeStarMaxDuration(unsigned long timeStarMaxDuration);

    float getTimeStarRandomOnFactor() const;

    void setTimeStarRandomOnFactor(float timeStarRandomOnFactor);

    float getTimeStarMinBrightness() const;

    void setTimeStarMinBrightness(float timeStarMinBrightness);

    float getTimeStarMaxBrightness() const;

    void setTimeStarMaxBrightness(float timeStarMaxBrightness);

    unsigned long getWaveDuration() const;

    void setWaveDuration(unsigned long waveTime);

    unsigned long getWaveTravelSpeed() const;

    void setWaveTravelSpeed(unsigned long waveTravelSpeed);

    float getWaveMinBrightness() const;

    void setWaveMinBrightness(float waveMinBrightness);

    float getWaveMaxBrightness() const;

    void setWaveMaxBrightness(float waveMaxBrightness);
};


#endif //TIL_INSTALLATION_H
