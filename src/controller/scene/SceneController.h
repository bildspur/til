//
// Created by Florian on 04.12.17.
//

#ifndef SILVA_SCENECONTROLLER_H
#define SILVA_SCENECONTROLLER_H

#include "BaseScene.h"

class SceneController : public BaseController {
private:
    BaseScene* activeScene;

public:
    explicit SceneController(BaseScene* defaultScene);

    void setup() override;

    void loop() override;

    BaseScene *getActiveScene() const;

    void setActiveScene(BaseScene *activeScene);
};

#endif //SILVA_SCENECONTROLLER_H
