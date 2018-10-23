//
// Created by Florian on 09.10.18.
//

#ifndef TIL_SERIALLIGHTRENDERER_H
#define TIL_SERIALLIGHTRENDERER_H


#include "LightRenderer.h"
#include "../../util/StopWatch.h"

class SerialLightRenderer : public LightRenderer {
private:
    u_long counter = 0;
    StopWatch watch = StopWatch();

public:
    explicit SerialLightRenderer(Installation *installation, float minBrightness = 0.0f, float maxBrightness = 1.0f);

    void setup() override;

    void loop() override;

    void render(LuboidPtr luboid) override;
};


#endif //TIL_SERIALLIGHTRENDERER_H
