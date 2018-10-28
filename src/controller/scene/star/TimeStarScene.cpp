//
// Created by Florian Bruggisser on 25.10.18.
//

#include "TimeStarScene.h"
#include "../../../util/FloatUtil.h"

TimeStarScene::TimeStarScene(Installation *installation) : BaseScene(
        "TimeStarScene", installation) {
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
        if (!star->isRunning(timeStamp) && FloatUtil::isRandomCalled(installation->getTimeStarRandomOnFactor())) {
            star->start(timeStamp, (unsigned long) lround(
                    random(installation->getTimeStarMinDuration(), random(installation->getTimeStarMaxDuration()))));
        }

        // update
        float brightness = star->getBrightness(timeStamp);
        float clampedBrightness = FloatUtil::mapFromLEDBrightness(brightness, installation->getTimeStarMinBrightness(),
                                                                  installation->getTimeStarMaxBrightness());
        installation->getLuboid(i)->setBrightness(clampedBrightness);
    }
}