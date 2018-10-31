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

    uint16_t starCount;

    TimeStarPtr *stars;

public:
    explicit TimeStarScene(Installation *installation);

    void setup() override;

    void loop() override;

    void resetStar(int id);
};


#endif //TIL_TIMESTARSCENE_H
