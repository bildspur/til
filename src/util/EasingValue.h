//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_EASINGFLOAT_H
#define SILVA_EASINGFLOAT_H


class EasingValue {
private:
    float value;
    float target;
    float easing;

public:
    explicit EasingValue(float value = 0.0, float easing = 0.1);

    void update();

    float get();

    int getInt();

    void set(float value);

    void setTarget(float value);

    float getTarget();

    void setEasing(float easing);

    float getEasing();
};


#endif //SILVA_EASINGFLOAT_H
