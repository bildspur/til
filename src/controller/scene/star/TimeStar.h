//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_TIMESTAR_H
#define TIL_TIMESTAR_H


class TimeStar {
    unsigned long startTime = 0;
    unsigned long duration = 0;

public:
    explicit TimeStar();

    bool isRunning(unsigned long timeStamp);

    void start(unsigned long timeStamp, unsigned long duration);

    float getBrightness(unsigned long timeStamp);

    void reset();
};


#endif //TIL_TIMESTAR_H
