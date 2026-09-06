#ifndef CHANGER_SYSTEM_H
#define CHANGER_SYSTEM_H

#include "isubsystem.h"
#include "ecs_components.h"

class ChangerSystem:public ISubSystem{
    private:
    public:
    bool setTexture();
    bool setFont();
    bool setText();
    bool setAcceleration();
    bool setVelocity();
    bool setPosition();
};
#endif