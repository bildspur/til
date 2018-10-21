//
// Created by Florian Bruggisser on 21.10.18.
//

#include "DMXLightRenderer.h"
#include "../../util/FloatUtil.h"

DMXLightRenderer::DMXLightRenderer(uint8_t pin, uint8_t lightAddressSize, Installation *installation,
                                   float minBrightness, float maxBrightness)
        : LightRenderer(installation, minBrightness, maxBrightness) {
    this->lightChannelSize = lightAddressSize;
    this->pin = pin;
    this->dmx = new DMXESPSerial();
}

void DMXLightRenderer::setup() {
    LightRenderer::setup();

    dmx->init(DMX_MAX_CHANNEL, pin);
}

void DMXLightRenderer::loop() {
    LightRenderer::loop();

    // send dmx bulk
    dmx->update();
}

void DMXLightRenderer::render(LuboidPtr luboid) {
    LightRenderer::render(luboid);

    // get address
    auto address = luboid->getId() * lightChannelSize;

    // map global brightness
    auto brightness = FloatUtil::map(luboid->getBrightness(),
                                     LUBOID_MIN_BRIGHTNESS, LUBOID_MAX_BRIGHTNESS,
                                     minBrightness, maxBrightness);

    // convert to dmx
    auto dmxValue = static_cast<uint8_t>(lround(
            FloatUtil::map(brightness, minBrightness, maxBrightness, DMX_MIN_VALUE, DMX_MAX_VALUE)));

    // set dmx
    dmx->write(address, dmxValue);
}
