//
// Created by Florian Bruggisser on 22.10.18.
//

#ifndef TIL_WAVESCENE_H
#define TIL_WAVESCENE_H


#include "BaseScene.h"
#include "../sensor/interaction/MotionSensor.h"

#define MAX_WAVES 10

class WaveScene : public BaseScene {
private:
    MotionSensor *motionSensor;

    unsigned long waves[MAX_WAVES];
    uint8_t nextWaveIndex = 0;

    bool updateLuboid(LuboidPtr luboid, unsigned long timeDiff);

public:
    explicit WaveScene(Installation *installation, MotionSensor *motionSensor);

    void setup() override;

    void loop() override;

    void pollNewWave();

    void startWave();
};


#endif //TIL_WAVESCENE_H
