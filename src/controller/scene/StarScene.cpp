//
// Created by Florian on 13.12.17.
//

#include <Arduino.h>
#include "StarScene.h"

StarScene::StarScene(Installation *installation) : BaseScene("StarScene", installation) {
    // init seed
    randomSeed(static_cast<unsigned long>(analogRead(0)));
}

void StarScene::setup() {
    BaseScene::setup();

    for(auto i = 0; i < installation->getSize(); i++)
    {
        auto luboid = installation->getLuboid(i);

        // turn off light
        luboid->turnOff(false);
    }
}

void StarScene::loop() {
    BaseScene::loop();

    for(auto i = 0; i < installation->getSize(); i++)
    {
        auto luboid = installation->getLuboid(i);

        // check if leaf is on
        if(luboid->getBrightness() > 0.75)
        {
            if(isRandomCalled(RANDOM_OFF_FACTOR))
                luboid->turnOff();
        }
        else
        {
            if(isRandomCalled(RANDOM_ON_FACTOR))
                luboid->setBrightness(static_cast<float>(random(50, 100) / 100.0));
        }
    }
}

bool StarScene::isRandomCalled(float factor) {
    return (random(0, 1000) / 1000.0) > factor;
}
