//
// Created by Florian on 27.11.17.
//
#ifndef SILVA_OTACONTROLLER_H
#define SILVA_OTACONTROLLER_H

#include <ArduinoOTA.h>
#include "../BaseController.h"

class OTAController : public BaseController {
private:
    const char *deviceName;
    const char *password;
    uint16_t port;

    void setupOTAOnError();

    void setupOTAOnProgress();

    void setupOTAOnEnd();

    void setupOTAOnStart();

    void setupOTAAuth();

public:
    OTAController(const char *deviceName, const char *password, uint16_t port);

    void setup() override;

    void loop() override;
};


#endif //SILVA_OTACONTROLLER_H