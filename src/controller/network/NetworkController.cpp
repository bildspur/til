//
// Created by Florian on 27.11.17.
//

#include "NetworkController.h"

NetworkController::NetworkController(const char *deviceName, const char *ssid, const char *password,
                                     WiFiMode_t wifiMode) {
    this->deviceName = deviceName;
    this->ssid = ssid;
    this->password = password;
    this->wifiMode = wifiMode;
}

void NetworkController::setup() {
    BaseController::setup();

    WiFi.hostname(deviceName);

    if(wifiMode == WIFI_STA)
    {
        initSTA();
        setupSTA();
    }
    else
    {
        setupAP();
    }

    setupMDNS();

    printNetworkInformation();
}

void NetworkController::loop() {
    BaseController::loop();

    // check for connection loss
    if (wifiMode == WIFI_STA && WiFi.status() != WL_CONNECTED)
    {
        Serial.println("lost connection...");
        setup();
    }
}

void NetworkController::initSTA() {
    Serial.println("init STA mode...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
}

void NetworkController::setupSTA() {
    uint8_t waitedDelays = 0;

    // wait till wifi is connected
    while (WiFi.status() != WL_CONNECTED) {
        waitedDelays++;

        // reset wifi
        if (waitedDelays > STA_MAX_DELAYS) {
            Serial.println();
            Serial.println("re-init wifi...");
            initSTA();
            waitedDelays = 0;
        }

        delay(100);
    }

    Serial.println("connected!");
}

void NetworkController::setupAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
}

void NetworkController::setupMDNS() {
    if (!MDNS.begin(deviceName)) {
        Serial.println("Error setting up MDNS responder!");
    }

    // Add service to MDNS-SD
    MDNS.addServiceTxt("osc", "udp", "mac", WiFi.macAddress());
}

void NetworkController::printNetworkInformation() {
    Serial.print("WiFi State: ");
    Serial.println(WiFi.status());

    Serial.print("Local IP address: ");
    Serial.println(getIPAddress());

    Serial.print("Mac Address: ");
    Serial.println(WiFi.macAddress());
}


String NetworkController::getIPAddress()
{
    if (wifiMode == WIFI_AP)
        return WiFi.softAPIP().toString();
    else
        return WiFi.localIP().toString();
}