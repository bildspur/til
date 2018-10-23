//
// Created by Florian Bruggisser on 23.10.18.
//

#ifndef TIL_STOPWATCH_H
#define TIL_STOPWATCH_H


class StopWatch {
private:
    unsigned long startTime = 0L;
    unsigned long stopTime = 0L;

    bool running = false;

public:
    explicit StopWatch();

    void start();

    void stop();

    unsigned long elapsed();
};


#endif //TIL_STOPWATCH_H
