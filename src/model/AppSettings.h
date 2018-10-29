//
// Created by Florian Bruggisser on 29.10.18.
//

#ifndef TIL_APPSETTINGS_H
#define TIL_APPSETTINGS_H

#define TIL_SETTINGS_VERSION 1000

struct AppSettings {
private:
    int version = TIL_SETTINGS_VERSION;

    // global settings
    float minBrightness = 0.15f;

    float maxBrightness = 0.5f;

    // time star scene settings
    unsigned long timeStarMinDuration = 3000L;

    unsigned long timeStarMaxDuration = 5000;

    float timeStarRandomOnFactor = 0.99f;

    float timeStarMinBrightness = 0.0f;

    float timeStarMaxBrightness = 0.70f;

    // wave settings
    unsigned long waveDuration = 500L;

    unsigned long waveTravelSpeed = 135L;

    float waveMinBrightness = 0.0f;

    float waveMaxBrightness = 1.0f;

public:
    int getVersion() const;

    float getMinBrightness() const;

    void setMinBrightness(float minBrightness);

    float getMaxBrightness() const;

    void setMaxBrightness(float maxBrightness);

    unsigned long getTimeStarMinDuration() const;

    void setTimeStarMinDuration(unsigned long timeStarMinDuration);

    unsigned long getTimeStarMaxDuration() const;

    void setTimeStarMaxDuration(unsigned long timeStarMaxDuration);

    float getTimeStarRandomOnFactor() const;

    void setTimeStarRandomOnFactor(float timeStarRandomOnFactor);

    float getTimeStarMinBrightness() const;

    void setTimeStarMinBrightness(float timeStarMinBrightness);

    float getTimeStarMaxBrightness() const;

    void setTimeStarMaxBrightness(float timeStarMaxBrightness);

    unsigned long getWaveDuration() const;

    void setWaveDuration(unsigned long waveDuration);

    unsigned long getWaveTravelSpeed() const;

    void setWaveTravelSpeed(unsigned long waveTravelSpeed);

    float getWaveMinBrightness() const;

    void setWaveMinBrightness(float waveMinBrightness);

    float getWaveMaxBrightness() const;

    void setWaveMaxBrightness(float waveMaxBrightness);
};


#endif //TIL_APPSETTINGS_H
