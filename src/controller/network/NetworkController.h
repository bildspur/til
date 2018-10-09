//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_NETWORKCONTROLLER_H
#define SILVA_NETWORKCONTROLLER_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <IPAddress.h>

#include "../BaseController.h"

#define STA_MAX_DELAYS 100

class NetworkController : public BaseController {
private:
    const char *deviceName;
    const char *ssid;
    const char *password;

    WiFiMode_t wifiMode;

    void initSTA();
    void setupSTA();
    void setupAP();
    void setupMDNS();
    String getIPAddress();

public:
    NetworkController(const char *deviceName, const char *ssid, const char *password, WiFiMode_t wifiMode = WIFI_AP);

    void setup() override;
    void loop() override;

    void printNetworkInformation();
};


#endif //SILVA_NETWORKCONTROLLER_H
