//
// Created by Florian Bruggisser on 21.10.18.
//

#ifndef TIL_DMXLIGHTRENDERER_H
#define TIL_DMXLIGHTRENDERER_H


#include "LightRenderer.h"

#define DMX_MAX_CHANNEL 512

#define DMX_MIN_VALUE 0
#define DMX_MAX_VALUE 255

class DMXLightRenderer : public LightRenderer {
private:
    uint8_t txPin;
    uint8_t lightChannelSize;
    uint8_t dmxBuffer[DMX_MAX_CHANNEL];

    void publishBuffer();

public:
    explicit DMXLightRenderer(uint8_t txPin, uint8_t lightAddressSize, Installation *installation,
                              float minBrightness = 0.0f, float maxBrightness = 1.0f);

    void setup() override;

    void loop() override;

    void render(LuboidPtr luboid) override;
};


#endif //TIL_DMXLIGHTRENDERER_H
