//
// Created by Florian on 06.12.17.
//

#include "LightRenderer.h"
#include "../../util/MathUtils.h"

LightRenderer::LightRenderer(Installation *installation) {
    this->installation = installation;
}

void LightRenderer::setup() {
    BaseController::setup();
}

void LightRenderer::loop() {
    BaseController::loop();

    for (auto i = 0; i < installation->getSize(); i++) {
        auto leaf = installation->getLuboid(i);
        render(leaf);
    }
}

void LightRenderer::render(LuboidPtr luboid) {
    // send out data
}

float LightRenderer::mapToGlobalBrightnessRange(float value) {
    return MathUtils::map(value,
                          LUBOID_MIN_BRIGHTNESS, LUBOID_MAX_BRIGHTNESS,
                          installation->getMinBrightness(), installation->getMaxBrightness());
}
