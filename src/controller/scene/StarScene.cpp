//
// Created by Florian on 13.12.17.
//

#include <Arduino.h>
#include "StarScene.h"
#include "../../util/FloatUtil.h"

StarScene::StarScene(Installation *installation) : BaseScene("StarScene", installation) {
    // init seed
}

void StarScene::setup() {
    BaseScene::setup();

    for (auto i = 0; i < installation->getSize(); i++) {
        auto luboid = installation->getLuboid(i);

        // turn off light
        luboid->turnOff(false);
    }
}

void StarScene::loop() {
    BaseScene::loop();

    for (auto i = 0; i < installation->getSize(); i++) {
        auto luboid = installation->getLuboid(i);

        // check if leaf is on
        if (luboid->getBrightness() > 0.75) {
            if (FloatUtil::isRandomCalled(RANDOM_OFF_FACTOR))
                luboid->turnOff();
        } else {
            if (FloatUtil::isRandomCalled(RANDOM_ON_FACTOR))
                luboid->setBrightness(static_cast<float>(random(50, 100) / 100.0));
        }
    }
}