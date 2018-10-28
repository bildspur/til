//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_FLOATUTIL_H
#define SILVA_FLOATUTIL_H


class MathUtils {
protected:
    MathUtils();

public:
    static float map(float value, float minIn, float maxIn, float minOut, float maxOut);

    static float limit(float value, float min, float max);

    static float windowedSine(float x);

    static bool isRandomCalled(float factor);

    static float mapFromLEDBrightness(float value, float minValue, float maxValue);

    static unsigned long secondsToMillis(unsigned long seconds);

    static unsigned long millisToSeconds(unsigned long millis);
};


#endif //SILVA_FLOATUTIL_H
