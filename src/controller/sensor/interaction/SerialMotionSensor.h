//
// Created by Florian Bruggisser on 22.10.18.
//

#ifndef TIL_SERIALMOTIONSENSOR_H
#define TIL_SERIALMOTIONSENSOR_H


#include "MotionSensor.h"

class SerialMotionSensor : public MotionSensor {
private:
    uint8_t rxPin;

public:
    explicit SerialMotionSensor(uint8_t rxPin, unsigned int updateFrequency = 250);

    void measure() override;
};


#endif //TIL_SERIALMOTIONSENSOR_H
