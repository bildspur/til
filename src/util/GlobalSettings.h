//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_GLOBALSETTINGS_H
#define TIL_GLOBALSETTINGS_H

#include <cstdint>

class GlobalSettings {
private:
    static float ledMinBrightness;
    static float ledMaxBrightness;

public:
    GlobalSettings() = delete;

    static void load();

    static void save();

    static float clampGlobalBrightness(float value, float minValue, float maxValue);

    static float getLedMinBrightness();

    static void setLedMinBrightness(float ledMinBrightness);

    static float getLedMaxBrightness();

    static void setLedMaxBrightness(float ledMaxBrightness);
};


#endif //TIL_GLOBALSETTINGS_H
