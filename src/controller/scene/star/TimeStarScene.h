//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_TIMESTARSCENE_H
#define TIL_TIMESTARSCENE_H


#include "../BaseScene.h"
#include "TimeStar.h"

class TimeStarScene : public BaseScene {
private:
    typedef TimeStar *TimeStarPtr;

    float randomOnFactor;

    float minBrightness;
    float maxBrightness;

    unsigned long minDuration;
    unsigned long maxDuration;

    uint16_t starCount;

    TimeStarPtr *stars;

public:
    explicit TimeStarScene(Installation *installation,
                           unsigned long minDuration,
                           unsigned long maxDuration,
                           float randomOnFactor = 0.95f,
                           float minBrightness = 0.0f,
                           float maxBrightness = 1.0f);

    void setup() override;

    void loop() override;
};


#endif //TIL_TIMESTARSCENE_H
