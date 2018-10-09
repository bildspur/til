//
// Created by Florian on 09.10.18.
//

#include <HardwareSerial.h>
#include "SerialLightRenderer.h"

SerialLightRenderer::SerialLightRenderer(Installation *installation, float minBrightness, float maxBrightness)
        : LightRenderer(installation, minBrightness, maxBrightness) {

}

void SerialLightRenderer::setup() {
    LightRenderer::setup();
}

void SerialLightRenderer::loop() {
    LightRenderer::loop();

    counter++;

    if(counter % 1000 == 0)
    {
        Serial.printf("%3d update\n", counter);
    }
}

void SerialLightRenderer::render(LuboidPtr luboid) {
    LightRenderer::render(luboid);
}
