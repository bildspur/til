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

    watch.start();
}

void SerialLightRenderer::loop() {
    LightRenderer::loop();

    if (monitorTimer.elapsed()) {
        String msg = "SLR:";

        for (int i = 0; i < installation->getSize(); i++) {
            msg += String(installation->getLuboid(i)->getBrightness()) + ";";
        }

        msg += "\n";
        Serial.println(msg);
    }

    /*
    counter++;
    if (counter % 100 == 0) {
        watch.stop();
        Serial.printf("%f\t%f\n", watch.elapsed() / 1000.0,
                      floor(1 / (watch.elapsed() / 1000.0 / 100)));
        watch.start();
    }
     */
}

void SerialLightRenderer::render(LuboidPtr luboid) {
    LightRenderer::render(luboid);
}
