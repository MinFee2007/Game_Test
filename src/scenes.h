#ifndef SCENES_H
#define SCENES_h

#include "iscene.h"
#include "system_ecs.h"
#include "ecs_components.h"

class SceneMainMenu:public IScene{
    private:
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