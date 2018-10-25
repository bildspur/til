//
// Created by Florian Bruggisser on 25.10.18.
//

#include "TimeStarScene.h"
#include "../../../util/FloatUtil.h"
#include "../../../util/GlobalSettings.h"

TimeStarScene::TimeStarScene(Installation *installation,
                             unsigned long minDuration,
                             unsigned long maxDuration,
                             float randomOnFactor,
                             float minBrightness,
                             float maxBrightness) : BaseScene(
        "TimeStarScene", installation) {
    this->minDuration = minDuration;
    this->maxDuration = maxDuration;
    this->randomOnFactor = randomOnFactor;
    this->minBrightness = minBrightness;
    this->maxBrightness = maxBrightness;
}


void TimeStarScene::setup() {
    BaseScene::setup();

    // setup stars
    this->starCount = installation->getSize();
    this->stars = new TimeStarPtr[starCount];

    // init stars
    for (auto i = 0; i < starCount; i++) {
        stars[i] = new TimeStar();
    }
}

void TimeStarScene::loop() {
    BaseScene::loop();

    auto timeStamp = millis();

    // rnd stars
    for (auto i = 0; i < starCount; i++) {
        auto star = stars[i];
        if (!star->isRunning(timeStamp) && FloatUtil::isRandomCalled(randomOnFactor))
            star->start(timeStamp, (unsigned long) lround(random(minDuration, maxDuration)));

        // update
        float brightness = star->getBrightness(timeStamp);
        float clampedBrightness = GlobalSettings::clampGlobalBrightness(brightness, minBrightness, maxBrightness);
        installation->getLuboid(i)->setBrightness(clampedBrightness);
    }
}