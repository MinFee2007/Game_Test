#ifndef SCENES_H
#define SCENES_H

#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>

#include "i_scene.h"

#include "system_all.h"
#include "system_ecs.h"
#include "system_time.h"

#include "o_ecs_components.h"

class SceneMainMenu:public IScene{
    private:
    std::string state;
    std::unordered_map<std::string,Entity*> entities;
    public:
    SceneMainMenu();
    void enter() override;
    void update() override;
    void print() override;
    void exit() override;
};

#endif