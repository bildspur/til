//
// Created by Florian on 28.11.17.
//

#include "BaseScene.h"

BaseScene::BaseScene(const char *name, Installation *installation) {
    this->name = name;
    this->installation = installation;
}

void BaseScene::setup() {
    BaseController::setup();
}

void BaseScene::loop() {
    BaseController::loop();

    // update leafs
    for(auto i = 0; i < installation->getSize(); i++)
    {
        installation->getLuboid(i)->update();
    }
}

const char * BaseScene::getName() const {
    return name;
}
