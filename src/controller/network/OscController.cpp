//
// Created by Florian on 27.11.17.
//

#include "OscController.h"

OscController::OscController(uint16_t inPort, uint16_t outPort) {
    this->inPort = inPort;
    this->outPort = outPort;
}

void OscController::setup() {
    BaseController::setup();

    Udp.begin(inPort);
}

void OscController::loop() {
    BaseController::loop();

    OSCMessage msg;
    int size;
    if ((size = Udp.parsePacket()) > 0) {
        while (size--)
            msg.fill(static_cast<uint8_t>(Udp.read()));

        if (!msg.hasError()) {

            // feed because of watchdog
            //ESP.wdtFeed();

            routeOSCMessage(msg);
        }
    }
}

void OscController::sendMessage(OSCMessage &msg) {
    Udp.beginPacket(broadcastIP, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
}

void OscController::routeOSCMessage(OSCMessage &msg) {
    if(onMessageReceivedCallback)
        onMessageReceivedCallback(msg);
}

void OscController::onMessageReceived(OscController::OSCHandlerFunction handler) {
    onMessageReceivedCallback = handler;
}

void OscController::send(const char *route, const char *value) {
    char buffer[CHAR_BUFFER_SIZE];
    sprintf(buffer, value);

    OSCMessage msg(route);
    msg.add(buffer);
    sendMessage(msg);
}

void OscController::send(const char *route, int value) {
    OSCMessage msg(route);
    msg.add(value);
    sendMessage(msg);
}

void OscController::send(const char *route, float value) {
    OSCMessage msg(route);
    msg.add(value);
    sendMessage(msg);
}
