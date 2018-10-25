//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_LIGHTRENDERER_H
#define SILVA_LIGHTRENDERER_H

#include "../BaseController.h"
#include "../../model/Installation.h"

class LightRenderer : public BaseController {
protected:
    explicit LightRenderer(Installation *installation);

    Installation *installation;

public:
    void setup() override;

    void loop() override;

    virtual void render(LuboidPtr luboid);

    float mapToGlobalBrightnessRange(float value);
};


#endif //SILVA_LIGHTRENDERER_H
