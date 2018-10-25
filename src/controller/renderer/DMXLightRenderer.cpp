//
// Created by Florian Bruggisser on 21.10.18.
//

#include <esp_task_wdt.h>
#include "DMXLightRenderer.h"
#include "../../util/FloatUtil.h"
#include "../driver/LXESP32DMX/LXESP32DMX.h"

DMXLightRenderer::DMXLightRenderer(uint8_t txPin, uint8_t lightAddressSize, Installation *installation,
                                   float minBrightness, float maxBrightness)
        : LightRenderer(installation) {
    this->lightChannelSize = lightAddressSize;
    this->txPin = txPin;
}

void DMXLightRenderer::setup() {
    LightRenderer::setup();

    pinMode(txPin, OUTPUT);
    ESP32DMX.startOutput(txPin);
}

void DMXLightRenderer::loop() {
    LightRenderer::loop();

    // send dmx bulk
    publishBuffer();
}

void DMXLightRenderer::render(LuboidPtr luboid) {
    LightRenderer::render(luboid);

    // get address
    auto address = luboid->getId() * lightChannelSize;

    // map global brightness
    auto brightness = mapToGlobalBrightnessRange(luboid->getBrightness());

    // convert to dmx
    auto dmxValue = static_cast<uint8_t>(lround(
            FloatUtil::map(brightness, LUBOID_MIN_BRIGHTNESS, LUBOID_MAX_BRIGHTNESS, DMX_MIN_VALUE, DMX_MAX_VALUE)));

    // set dmx on all 4 channels
    for (int i = 0; i < lightChannelSize; i++) {
        dmxBuffer[static_cast<uint16_t>(address + i)] = dmxValue;
    }
}

void DMXLightRenderer::publishBuffer() {
    xSemaphoreTake(ESP32DMX.lxDataLock, portMAX_DELAY);
    for (int i = 1; i < DMX_MAX_FRAME; i++) {
        ESP32DMX.setSlot(i, dmxBuffer[i]);
    }
    xSemaphoreGive(ESP32DMX.lxDataLock);
}
