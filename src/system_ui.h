#ifndef SYSTEM_UI_H
#define SYSTEM_UI_H

#include <vector>

#include "isubsystem.h"
#include "system_ecs.h"

class UISystem:public ISubSystem{
    private:
    std::vector<Entity*> UInodes;
    std::vector<Entity*> GUInodes;
    public:

};
#endif