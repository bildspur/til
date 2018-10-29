#include <Arduino.h>
#include <Wire.h>
#include <ESPmDNS.h>
#include <inttypes.h>

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
#include "controller/renderer/SerialLightRenderer.h"
#include "controller/renderer/DMXLightRenderer.h"
#include "controller/scene/WaveScene.h"
#include "controller/sensor/interaction/MotionSensor.h"
#include "controller/sensor/interaction/SerialMotionSensor.h"
#include "controller/scene/star/TimeStarScene.h"
#include "util/MathUtils.h"

// global
#define INSTALLATION_DEBUG true

#define LUBOID_COUNT 33

// motion
#define MOTION_RX_PIN 12
#define MOTION_BAUD_RATE 9600
#define MOTION_UPDATE_FREQ 100

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

// dmx
#define DMX_TX_PIN 2
#define DMX_LIGHT_ADDRESS_SIZE 4

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

// renderer
LightRenderer *renderer = new DMXLightRenderer(DMX_TX_PIN, DMX_LIGHT_ADDRESS_SIZE, &installation);
LightRenderer *debugRenderer = new SerialLightRenderer(&installation);

// sensors
MotionSensor *motionSensor = new SerialMotionSensor(MOTION_RX_PIN, MOTION_BAUD_RATE, MOTION_UPDATE_FREQ);

// scenes
//StarScene starScene = StarScene(&installation);
TimeStarScene timeStarScene = TimeStarScene(&installation);
WaveScene waveScene = WaveScene(&installation, motionSensor);

auto sceneController = SceneController(&timeStarScene);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        //debugRenderer,
        renderer,
        motionSensor,
        &sceneController,
        // important to be after scene controller -> overwrite scene
        &waveScene
};

// methods
void handleOsc(OSCMessage &msg);

void changeScene(BaseScene *scene);

void sendRefresh();

void setup() {
    Serial.begin(BAUD_RATE);

    // wait some seconds for debugging
    delay(5000);

    // setup random seed
    randomSeed(static_cast<unsigned long>(analogRead(0)));

    // setup luboids
    installation.initLuboids();

    // load settings
    installation.loadFromEEPROM();

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);

    // add osc mdns
    MDNS.addService("_osc", "_udp", OSC_IN_PORT);

    Serial.println("setup finished!");
    sendRefresh();
}

void loop() {
    // loop controllers
    for (auto &controller : controllers) {
        controller->loop();
    }
}

void changeScene(BaseScene *scene) {
    sceneController.setActiveScene(scene);

    // setup scene
    sceneController.getActiveScene()->setup();
}

void handleOsc(OSCMessage &msg) {
    // global
    msg.dispatch("/til/brightness/min", [](OSCMessage &msg) {
        installation.getSettings().setMinBrightness(msg.getFloat(0));
    });

    msg.dispatch("/til/brightness/max", [](OSCMessage &msg) {
        installation.getSettings().setMaxBrightness(msg.getFloat(0));
    });

    msg.dispatch("/til/scenemanager/on", [](OSCMessage &msg) {
        sceneController.setRunning(!sceneController.isRunning());
    });

    // time star
    msg.dispatch("/til/timestar/brightness/min", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMinBrightness(msg.getFloat(0));
    });

    msg.dispatch("/til/timestar/brightness/max", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMaxBrightness(msg.getFloat(0));
    });

    msg.dispatch("/til/timestar/randomFactor", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarRandomOnFactor(msg.getFloat(0));
    });

    msg.dispatch("/til/timestar/duration/min", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMinDuration(
                MathUtils::secondsToMillis(static_cast<unsigned long>(msg.getFloat(0))));
    });

    msg.dispatch("/til/timestar/duration/max", [](OSCMessage &msg) {
        installation.getSettings().setTimeStarMaxDuration(
                MathUtils::secondsToMillis(static_cast<unsigned long>(msg.getFloat(0))));
    });

    // wave
    msg.dispatch("/til/wave/brightness/min", [](OSCMessage &msg) {
        installation.getSettings().setWaveMinBrightness(msg.getFloat(0));
    });

    msg.dispatch("/til/wave/brightness/max", [](OSCMessage &msg) {
        installation.getSettings().setWaveMaxBrightness(msg.getFloat(0));
    });

    msg.dispatch("/til/wave/duration", [](OSCMessage &msg) {
        installation.getSettings().setWaveDuration(msg.getFloat(0));
    });

    msg.dispatch("/til/wave/travelspeed", [](OSCMessage &msg) {
        installation.getSettings().setWaveTravelSpeed(msg.getFloat(0));
    });

    // controls
    msg.dispatch("/til/installation/on", [](OSCMessage &msg) {
        installation.turnOn();
    });

    msg.dispatch("/til/installation/off", [](OSCMessage &msg) {
        installation.turnOff();
    });

    msg.dispatch("/til/wave", [](OSCMessage &msg) {
        waveScene.startWave();
    });

    msg.dispatch("/til/wave", [](OSCMessage &msg) {
        waveScene.startWave();
    });

    msg.dispatch("/til/refresh", [](OSCMessage &msg) {
        sendRefresh();
    });

    msg.dispatch("/til/settings/load", [](OSCMessage &msg) {
        installation.loadFromEEPROM();
        osc.send("/til/status", "Status: loaded!");
    });

    msg.dispatch("/til/settings/save", [](OSCMessage &msg) {
        installation.saveToEEPROM();
        osc.send("/til/status", "Status: saved!");
    });

    sendRefresh();
}

void sendRefresh() {
    // global
    osc.send("/til/brightness/min", installation.getSettings().getMinBrightness());
    osc.send("/til/brightness/max", installation.getSettings().getMaxBrightness());
    osc.send("/til/scenemanager/on", sceneController.isRunning());

    // time star
    osc.send("/til/timestar/brightness/min", installation.getSettings().getTimeStarMinBrightness());
    osc.send("/til/timestar/brightness/max", installation.getSettings().getTimeStarMaxBrightness());
    osc.send("/til/timestar/randomFactor", installation.getSettings().getTimeStarRandomOnFactor());
    osc.send("/til/timestar/duration/min",
             static_cast<float>(MathUtils::millisToSeconds(installation.getSettings().getTimeStarMinDuration())));
    osc.send("/til/timestar/duration/max",
             static_cast<float>(MathUtils::millisToSeconds(installation.getSettings().getTimeStarMaxDuration())));

    // wave
    osc.send("/til/wave/brightness/min", installation.getSettings().getWaveMinBrightness());
    osc.send("/til/wave/brightness/max", installation.getSettings().getWaveMaxBrightness());
    osc.send("/til/wave/duration", static_cast<float>(installation.getSettings().getWaveDuration()));
    osc.send("/til/wave/travelspeed", static_cast<float>(installation.getSettings().getWaveTravelSpeed()));
}