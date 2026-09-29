#ifndef SCENES_H
#define SCENES_H

#include <SDL3/SDL.h>
#include "i_scene.h"

#include "system_all.h"
#include "system_ecs.h"

#include "o_ecs_components.h"

class SceneMainMenu:public IScene{
    private:
    std::string state;
    public:
    SceneMainMenu();
    void enter() override;
    void update() override;
    void print() override;
    void exit() override;
};

#endif