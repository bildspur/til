//
// Created by Florian on 28.11.17.
//

#ifndef SILVA_BASESCENE_H
#define SILVA_BASESCENE_H

#include "../BaseController.h"
#include "../../model/Installation.h"

class BaseScene : public BaseController {
private:

protected:
    explicit BaseScene(const char *name, Installation *installation);

    Installation *installation;

    const char *name;

public:
    void setup() override;

    void loop() override;

    const char * getName() const;
};


#endif //SILVA_BASESCENE_H
