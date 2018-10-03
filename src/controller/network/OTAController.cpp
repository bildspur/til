//
// Created by Florian on 27.11.17.
//
#include "OTAController.h"

OTAController::OTAController(const char *deviceName, const char *password, uint16_t port) {
    this->deviceName = deviceName;
    this->password = password;
    this->port = port;
}

void OTAController::setup() {
    BaseController::setup();

    setupOTAAuth();
    setupOTAOnStart();
    setupOTAOnEnd();
    setupOTAOnProgress();
    setupOTAOnError();

    ArduinoOTA.begin();
}

void OTAController::loop() {
    BaseController::loop();

    ArduinoOTA.handle();
}

void OTAController::setupOTAAuth()
{
    ArduinoOTA.setPort(port);
    ArduinoOTA.setHostname(deviceName);
    ArduinoOTA.setPassword(password);
}

void OTAController::setupOTAOnStart()
{
    ArduinoOTA.onStart([]() {
        Serial.println("Start updating ...");
    });
}

void OTAController::setupOTAOnEnd()
{
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
}

void OTAController::setupOTAOnProgress()
{
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
}

void OTAController::setupOTAOnError()
{
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");

        ESP.restart();
    });
}