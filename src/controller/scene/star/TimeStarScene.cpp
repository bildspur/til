//
// Created by Florian Bruggisser on 25.10.18.
//

#include "TimeStarScene.h"
#include "../../../util/MathUtils.h"

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
        if (!star->isRunning(timeStamp) &&
            MathUtils::isRandomCalled(installation->getSettings().getTimeStarRandomOnFactor())) {
            star->start(timeStamp, (unsigned long) lround(
                    random(installation->getSettings().getTimeStarMinDuration(),
                           random(installation->getSettings().getTimeStarMaxDuration()))));
        }

        // update
        float brightness = star->getBrightness(timeStamp);
        float clampedBrightness = MathUtils::mapFromLEDBrightness(brightness,
                                                                  installation->getSettings().getTimeStarMinBrightness(),
                                                                  installation->getSettings().getTimeStarMaxBrightness());
        installation->getLuboid(i)->setBrightness(clampedBrightness);
    }
}

void TimeStarScene::resetStar(int id) {
    stars[id]->reset();
}
