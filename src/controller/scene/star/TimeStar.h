//
// Created by Florian Bruggisser on 25.10.18.
//

#ifndef TIL_TIMESTAR_H
#define TIL_TIMESTAR_H


class TimeStar {
    unsigned long startTime;
    unsigned long duration;

public:
    explicit TimeStar();

    bool isRunning(unsigned long timeStamp);

    void start(unsigned long timeStamp, unsigned long duration);

    float getBrightness(unsigned long timeStamp);
};


#endif //TIL_TIMESTAR_H
