#ifndef SYSTEM_UI_H
#define SYSTEM_UI_H

#include <vector>

#include "i_subsystem.h"
#include "system_ecs.h"

class UISystem:public ISubSystem{
    private:
    std::vector<Entity*> UInodes;
    std::vector<Entity*> GUInodes;
    public:
    void init() override {}
    void update() override {}
    void destruct() override {}
};
#endif