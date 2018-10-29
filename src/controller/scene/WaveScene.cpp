//
// Created by Florian Bruggisser on 22.10.18.
//

#include "WaveScene.h"
#include "../../util/MathUtils.h"

WaveScene::WaveScene(Installation *installation,
                     MotionSensor *motionSensor) : BaseScene("WaveScene",
                                                             installation) {
    this->motionSensor = motionSensor;;
}

void WaveScene::setup() {
    BaseScene::setup();

    // reset waves
    for (unsigned long &wave : this->waves) {
        wave = 0L;
    }
}

void WaveScene::loop() {
    BaseScene::loop();

    // check for new wave
    pollNewWave();

    // update current waves
    for (auto waveStart : waves) {
        // check if is relevant
        if (waveStart == 0)
            continue;

        // calculate timediff
        auto timeDiff = millis() - waveStart;

        // update luboids
        auto waveIsRelevant = false;
        for (auto i = 0; i < installation->getSize(); i++) {
            auto luboid = installation->getLuboid(i);

            if (updateLuboid(luboid, timeDiff))
                waveIsRelevant = true;
        }

        // stop wave if necessary
        if (!waveIsRelevant)
            waveStart = 0;
    }
}

bool WaveScene::updateLuboid(LuboidPtr luboid, unsigned long timeDiff) {
    // do nothing till nmt relevant
    auto ldiff = timeDiff - (luboid->getId() * installation->getSettings().getWaveTravelSpeed());

    // wave relevant but not yet
    if (ldiff < 0L)
        return true;

    float x = ldiff / (float) installation->getSettings().getWaveDuration();

    // wave not relevant anymore
    if (x > 1.0f)
        return false;

    // get brightness and update
    float brightness = MathUtils::windowedSine(x);
    float clamped = MathUtils::mapFromLEDBrightness(brightness, installation->getSettings().getWaveMinBrightness(),
                                                    installation->getSettings().getWaveMaxBrightness());
    luboid->setBrightness(clamped);
    return true;
}

void WaveScene::pollNewWave() {
    // check for wave and clear flag
    if (motionSensor->isMotionDetected(true)) {
        startWave();
    }
}

void WaveScene::startWave() {
    waves[nextWaveIndex] = millis();
    nextWaveIndex = static_cast<uint8_t>((nextWaveIndex + 1) % MAX_WAVES);
}
