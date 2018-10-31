//
// Created by Florian Bruggisser on 22.10.18.
//

#include "WaveScene.h"
#include "../../util/MathUtils.h"

WaveScene::WaveScene(Installation *installation,
                     MotionSensor *motionSensor,
                     TimeStarScene *starScene) : BaseScene("WaveScene",
                                                           installation) {
    this->motionSensor = motionSensor;
    this->starScene = starScene;
}

void WaveScene::setup() {
    BaseScene::setup();

    // reset waves
    for (unsigned long &wave : waves) {
        wave = 0UL;
    }
}

void WaveScene::loop() {
    BaseScene::loop();

    // check for new wave
    pollNewWave();

    // update current waves
    for (unsigned long &waveStart : this->waves) {
        // check if is relevant
        if (waveStart == 0)
            continue;

        Serial.printf("wave relevant: %d\n", &waveStart);

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
            waveStart = 0UL;
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
    if (x > 1.0f) {
        // todo: fix nicer
        if (x < 1.1f) {
            // reset star sine
            Serial.printf("reseting star %d\n", luboid->getId());
            starScene->resetStar(luboid->getId());
        }
        return false;
    }

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
