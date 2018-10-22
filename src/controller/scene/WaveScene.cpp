//
// Created by Florian Bruggisser on 22.10.18.
//

#include "WaveScene.h"

WaveScene::WaveScene(Installation *installation, unsigned long waveTime,
                     unsigned long waveTravelSpeed) : BaseScene("WaveScene", installation) {
    this->waveTime = waveTime;
    this->waveTravelSpeed = waveTravelSpeed;
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
    auto ldiff = timeDiff - (luboid->getId() * waveTravelSpeed);

    // wave relevant but not yet
    if (ldiff < 0L)
        return true;

    float x = ldiff / (float) waveTime;

    // wave not relevant anymore
    if (x > 1.0f)
        return false;

    // get brightness and update
    float brightness = windowedSine(x);
    luboid->setBrightness(brightness);
    return true;
}

float WaveScene::windowedSine(float x) {
    if (x < 0.0f || x > 1.0f)
        return 0.0f;

    // calculate sine
    return static_cast<float>(0.5 * (1 + sin(2 * PI * x - (PI / 2))));
}

void WaveScene::pollNewWave() {
    // check for wave
    // todo add wave check!
    if (false) {
        waves[nextWaveIndex] = millis();
        nextWaveIndex = static_cast<uint8_t>((nextWaveIndex + 1) % MAX_WAVES);

        // clean flags
        //thereIsANewWave = false;
    }
}
