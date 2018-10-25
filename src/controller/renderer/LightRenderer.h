//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_LIGHTRENDERER_H
#define SILVA_LIGHTRENDERER_H

#include "../BaseController.h"
#include "../../model/Installation.h"

class LightRenderer : public BaseController {
protected:
    explicit LightRenderer(Installation *installation, float minBrightness = 0.0f, float maxBrightness = 1.0f);

    Installation *installation;

    float minBrightness;
    float maxBrightness;

public:
    void setup() override;

    void loop() override;

    virtual void render(LuboidPtr luboid);

    float getMinBrightness() const;

    void setMinBrightness(float minBrightness);

    float getMaxBrightness() const;

    void setMaxBrightness(float maxBrightness);
};


#endif //SILVA_LIGHTRENDERER_H
