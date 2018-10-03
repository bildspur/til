#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <Wire.h>

#include "controller/BaseController.h"
#include "model/Luboid.h"
#include "model/Installation.h"
#include "controller/network/NetworkController.h"
#include "controller/network/OTAController.h"
#include "controller/network/OscController.h"
#include "controller/renderer/LightRenderer.h"
#include "controller/scene/BaseScene.h"
#include "controller/scene/StarScene.h"
#include "controller/scene/SceneController.h"

// global
#define INSTALLATION_DEBUG true

#define LUBOID_COUNT 30

#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255

// serial
#define BAUD_RATE 115200

// network
#define DEVICE_NAME "til-master"

#define SSID_NAME "til"
#define SSID_PASSWORD "TILbildspur"

#define OTA_PASSWORD "bildspur"
#define OTA_PORT 8266

#define OSC_OUT_PORT 9000
#define OSC_IN_PORT 8000

#define EDIT_UI_TIME 3000

// typedefs
typedef BaseController *BaseControllerPtr;
typedef Luboid *LuboidPtr;

// variables
LuboidPtr luboids[LUBOID_COUNT];
auto installation = Installation(LUBOID_COUNT, luboids);

// controllers
auto network = NetworkController(DEVICE_NAME, SSID_NAME, SSID_PASSWORD, WIFI_AP);
auto ota = OTAController(DEVICE_NAME, OTA_PASSWORD, OTA_PORT);
auto osc = OscController(OSC_IN_PORT, OSC_OUT_PORT);

LightRenderer *renderer = nullptr; // todo: initialise light renderer

// scenes
auto starScene = StarScene(&installation);

auto sceneController = SceneController(&starScene);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        renderer,
        &sceneController
};

// methods
void handleOsc(OSCMessage &msg);
void changeScene(BaseScene *scene);


void setup() {
    Serial.begin(BAUD_RATE);

    // wait 3000 seconds for debugging
    delay(3000);

    // setup wire
    Wire.begin(D2, D1);

    // setup leafs
    installation.loadLuboids();

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);

    // add osc mdns
    MDNS.addService("osc", "udp", OSC_IN_PORT);

    Serial.println("setup finished!");
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}

void changeScene(BaseScene *scene)
{
    sceneController.setActiveScene(scene);

    // setup scene
    sceneController.getActiveScene()->setup();
}

void handleOsc(OSCMessage &msg) {
    /*
    msg.dispatch("/til/scene/tree", [](OSCMessage &msg) {
        changeScene(&treeScene);
    });
     */
}