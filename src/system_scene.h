#ifndef SYSTEM_SCENE_H
#define SYSTEM_SCENE_H

#include <memory>

#include "isubsystem.h"
#include "system_all.h"

class IScene {
public:
    virtual void onEnter()=0;
    virtual void onUpdate()=0;
    virtual void onExit()=0;
    virtual ~IScene()=default;
};

class SceneSystem:public ISubSystem {
private:
    std::unique_ptr<IScene> currentScene;
    std::unique_ptr<IScene> nextScene;
public:
    void init() override {}

    void changeScene(std::unique_ptr<IScene> newScene){
        nextScene=std::move(newScene);
    }

    void update() override {
        if (nextScene){
            if (currentScene){
                currentScene->onExit();
                AllSystem::getInstance().getSubSystem<EntityComponentSystem>()->destruct();
            }
            currentScene=std::move(nextScene);
            currentScene->onEnter();
        }

        if (currentScene){
            currentScene->onUpdate();
        }
    }

    void destruct() override {
        if (currentScene) currentScene->onExit();
    }
};
#endif