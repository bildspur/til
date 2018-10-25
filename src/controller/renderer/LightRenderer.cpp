//
// Created by Florian on 06.12.17.
//

#include "LightRenderer.h"

LightRenderer::LightRenderer(Installation *installation, float minBrightness, float maxBrightness) {
    this->installation = installation;
    this->minBrightness = minBrightness;
    this->maxBrightness = maxBrightness;
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

float LightRenderer::getMinBrightness() const {
    return minBrightness;
}

void LightRenderer::setMinBrightness(float minBrightness) {
    LightRenderer::minBrightness = minBrightness;
}

float LightRenderer::getMaxBrightness() const {
    return maxBrightness;
}

void LightRenderer::setMaxBrightness(float maxBrightness) {
    LightRenderer::maxBrightness = maxBrightness;
}
