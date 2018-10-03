//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_OSCCONTROLLER_H
#define SILVA_OSCCONTROLLER_H


#include <cstdint>
#include <IPAddress.h>
#include <OSCMessage.h>
#include <WiFiUdp.h>

// exclude min and max
#undef max
#undef min

#include <functional>
#include "../BaseController.h"

#define CHAR_BUFFER_SIZE 16

class OscController : public BaseController {
private:
    typedef std::function<void(OSCMessage &msg)> OSCHandlerFunction;

    const IPAddress broadcastIP = IPAddress(255, 255, 255, 255);

    uint16_t inPort;
    uint16_t outPort;

    WiFiUDP Udp;

    OSCHandlerFunction onMessageReceivedCallback;

    void routeOSCMessage(OSCMessage &msg);

public:
    OscController(uint16_t inPort, uint16_t outPort);

    void setup() override;

    void loop() override;

    void sendMessage(OSCMessage &msg);

    void onMessageReceived(OSCHandlerFunction handler);

    void send(const char *route, const char *value);

    void send(const char *route, int value);

    void send(const char *route, float value);
};


#endif //SILVA_OSCCONTROLLER_H
