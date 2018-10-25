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

    unsigned long waveTime;
    unsigned long waveTravelSpeed;

    bool updateLuboid(LuboidPtr luboid, unsigned long timeDiff);

    float minBrightness;
    float maxBrightness;

public:
    explicit WaveScene(Installation *installation, MotionSensor *motionSensor, unsigned long waveTime,
                       unsigned long waveTravelSpeed, float minBrightness = 0.0f, float maxBrightness = 1.0f);

    void setup() override;

    void loop() override;

    void pollNewWave();

    void startWave();
};


#endif //TIL_WAVESCENE_H
