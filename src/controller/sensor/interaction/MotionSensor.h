//
// Created by Florian on 29.11.17.
//

#ifndef TIL_MOTIONSENSOR_H
#define TIL_MOTIONSENSOR_H


#include <cstdint>
#include "../../BaseController.h"
#include "../../../util/Timer.h"

class MotionSensor : public BaseController {
private:

protected:
    explicit MotionSensor(unsigned int updateFrequency = 250);

    bool motionDetected = false;

    bool running = true;

    Timer *timer;

public:
    void setup() override;

    void loop() override;

    virtual void measure();

    virtual bool isMotionDetected(bool clearFlag = false);

    bool isRunning() const;

    void setRunning(bool running);
};

#endif //TIL_MOTIONSENSOR_H
