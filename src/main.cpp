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
#include "util/GlobalSettings.h"
#include "controller/scene/star/TimeStarScene.h"

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

// time star scene
#define TIME_STAR_MIN_DURATION 5000L
#define TIME_STAR_MAX_DURATION 10000L
#define TIME_STAR_RANDOM_ON_FACTOR 0.95f
#define TIME_STAR_MIN_BRIGHTNESS 0.0f
#define TIME_STAR_MAX_BRIGHTNESS 1.0f

// wave (ms)
#define WAVE_TIME 3000
#define WAVE_TRAVEL_SPEED 500
#define WAVE_MIN_BRIGHTNESS 0.0f
#define WAVE_MAX_BRIGHTNESS 1.0f

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
StarScene starScene = StarScene(&installation);
TimeStarScene timeStarScene = TimeStarScene(&installation,
                                            TIME_STAR_MIN_DURATION,
                                            TIME_STAR_MAX_DURATION,
                                            TIME_STAR_RANDOM_ON_FACTOR,
                                            TIME_STAR_MIN_BRIGHTNESS,
                                            TIME_STAR_MAX_BRIGHTNESS);
WaveScene waveScene = WaveScene(&installation, motionSensor,
                                WAVE_TIME,
                                WAVE_TRAVEL_SPEED,
                                WAVE_MIN_BRIGHTNESS,
                                WAVE_MAX_BRIGHTNESS);

auto sceneController = SceneController(&timeStarScene);

// controller list
BaseControllerPtr controllers[] = {
        &network,
        &ota,
        &osc,
        debugRenderer,
        renderer,
        motionSensor,
        &sceneController,
        // important to be after scene controller -> overwrite scene
        &waveScene
};

// methods
void handleOsc(OSCMessage &msg);

void changeScene(BaseScene *scene);


void setup() {
    Serial.begin(BAUD_RATE);

    // wait some seconds for debugging
    delay(5000);

    // setup random seed
    randomSeed(static_cast<unsigned long>(analogRead(0)));

    // load settings
    GlobalSettings::load();

    // apply settings to renderer
    renderer->setMinBrightness(GlobalSettings::getLedMinBrightness());
    renderer->setMaxBrightness(GlobalSettings::getLedMinBrightness());

    // setup luboids
    installation.initLuboids();

    // setup controllers
    for (auto &controller : controllers) {
        controller->setup();
    }

    // setup handlers
    osc.onMessageReceived(handleOsc);

    // add osc mdns
    MDNS.addService("_osc", "_udp", OSC_IN_PORT);

    Serial.println("setup finished!");
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
    /*
    msg.dispatch("/til/scene/tree", [](OSCMessage &msg) {
        changeScene(&treeScene);
    });
     */
}