//
// Created by Florian on 04.12.17.
//

#include "SceneController.h"

SceneController::SceneController(BaseScene *defaultScene) {
    activeScene = defaultScene;
}

void SceneController::setup() {
    BaseController::setup();

    activeScene->setup();
}

void SceneController::loop() {
    BaseController::loop();

    activeScene->loop();
}

BaseScene *SceneController::getActiveScene() const {
    return activeScene;
}

void SceneController::setActiveScene(BaseScene *activeScene) {
    SceneController::activeScene = activeScene;
}
