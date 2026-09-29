#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <SDL3/SDL.h>

#include "i_subsystem.h"

#include "system_all.h"
#include "system_ecs.h"
#include "system_event.h"
#include "system_time.h"
#include "system_resource.h"
#include "system_ui.h"
#include "system_scene.h"

#include "o_scenes.h"

class ManagerSystem:public ISubSystem{
    private:
    bool isChange;
    public:
    ManagerSystem();
    bool getChange() const;
    void toggleChange();
    void setChange(bool change);
    void init() override;
    void update() override;
    void destruct() override;
};

#endif