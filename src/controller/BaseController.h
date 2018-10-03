//
// Created by Florian on 27.11.17.
//

#ifndef SILVA_BASECONTROLLER_H
#define SILVA_BASECONTROLLER_H


class BaseController {

protected:
    BaseController();

public:
    virtual void setup();
    virtual void loop();
};


#endif //SILVA_BASECONTROLLER_H
