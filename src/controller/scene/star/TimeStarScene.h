//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_TIMESTARSCENE_H
#define TIL_TIMESTARSCENE_H


#include "../BaseScene.h"

class TimeStarScene : public BaseScene {
private:
    float randomOnFactor;
    float randomOffFactor;

    static bool isRandomCalled(float factor);

public:
    explicit TimeStarScene(Installation *installation, float randomOnFactor = 0.95f, float randomOffFactor = 0.9f);

    void setup() override;

    void loop() override;
};


#endif //TIL_TIMESTARSCENE_H
