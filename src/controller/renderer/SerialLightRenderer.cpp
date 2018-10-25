//
// Created by Florian on 09.10.18.
//

#include <HardwareSerial.h>
#include "SerialLightRenderer.h"

SerialLightRenderer::SerialLightRenderer(Installation *installation, float minBrightness, float maxBrightness)
        : LightRenderer(installation) {

}

void SerialLightRenderer::setup() {
    LightRenderer::setup();

    watch.start();
}

void SerialLightRenderer::loop() {
    LightRenderer::loop();

    if (monitorTimer.elapsed()) {
        String msg = "SLR;";

        for (int i = 0; i < installation->getSize(); i++) {
            auto brightness = mapToGlobalBrightnessRange(installation->getLuboid(i)->getBrightness());
            msg += String(brightness) + ";";
        }

        msg += "\n";
        Serial.println(msg);
    }
}

void SerialLightRenderer::render(LuboidPtr luboid) {
    LightRenderer::render(luboid);
}
