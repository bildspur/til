//
// Created by Florian Bruggisser on 21.10.18.
//

#ifndef TIL_DMXLIGHTRENDERER_H
#define TIL_DMXLIGHTRENDERER_H


#include <ESPDMX.h>
#include "LightRenderer.h"

#define DMX_MAX_CHANNEL 512

class DMXLightRenderer : public LightRenderer {
private:
    DMXESPSerial *dmx;
    uint8_t pin;
    uint8_t lightChannelSize;

public:
    explicit DMXLightRenderer(uint8_t pin, uint8_t lightAddressSize, Installation *installation,
                              float minBrightness = 0.0f, float maxBrightness = 1.0f);

    void setup() override;

    void loop() override;

    void render(LuboidPtr luboid) override;
};


#endif //TIL_DMXLIGHTRENDERER_H
