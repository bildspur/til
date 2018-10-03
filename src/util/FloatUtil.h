//
// Created by Florian on 06.12.17.
//

#ifndef SILVA_FLOATUTIL_H
#define SILVA_FLOATUTIL_H


class FloatUtil {
protected:
    FloatUtil();

public:
    static float map(float value, float minIn, float maxIn, float minOut, float maxOut);
    static float limit(float value, float min, float max);
};


#endif //SILVA_FLOATUTIL_H
