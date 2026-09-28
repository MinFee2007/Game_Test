#ifndef SCENES_H
#define SCENES_h

#include "i_scene.h"
#include "system_ecs.h"
#include "o_ecs_components.h"

class SceneMainMenu:public IScene{
    private:
    std::string state;
    std::vector<Entity*> entities;
    public:
    SceneMainMenu(){

    }
    void onEnter() override {

    }
    void onUpdate() override {

    }
    void onExit() override {

    }
};

#endif