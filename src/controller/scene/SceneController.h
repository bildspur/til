//
// Created by Florian on 04.12.17.
//

#ifndef SILVA_SCENECONTROLLER_H
#define SILVA_SCENECONTROLLER_H

#include "BaseScene.h"

class SceneController : public BaseController {
private:
    BaseScene *activeScene;

    bool running = true;

public:
    explicit SceneController(BaseScene *defaultScene);

    void setup() override;

    void loop() override;

    BaseScene *getActiveScene() const;

    void setActiveScene(BaseScene *activeScene);

    bool isRunning() const;

    void setRunning(bool running);
};

#endif //SILVA_SCENECONTROLLER_H
