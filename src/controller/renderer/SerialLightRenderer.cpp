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


    counter++;
    if (counter % 100 == 0) {
        watch.stop();
        Serial.printf("%f\t%f\n", watch.elapsed() / 1000.0,
                      floor(1 / (watch.elapsed() / 1000.0 / 100)));

        /*Serial.printf("Took %f seconds\tframeRate: %f\n", watch.elapsed() / 1000.0,
                      floor(1 / (watch.elapsed() / 1000.0 / 100)));
                      */
        //Serial.printf("%3d update -> luboid 0: %3f\n", counter, installation->getLuboid(0)->getBrightness());
        watch.start();
    }
}

void SerialLightRenderer::render(LuboidPtr luboid) {
    LightRenderer::render(luboid);
}
