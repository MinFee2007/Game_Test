#ifndef SYSTEM_SCENE_H
#define SYSTEM_SCENE_H

#include <memory>

#include "i_subsystem.h"
#include "i_scene.h"

class SceneSystem:public ISubSystem {
    private:
    std::unique_ptr<IScene> currentScene;
    std::unique_ptr<IScene> nextScene;
    public:
    void init() override {
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            log->write(NOTIFICATION,"Scene system is initialized successfully");
        }
    }

    void changeScene(std::unique_ptr<IScene> newScene){
        nextScene=std::move(newScene);
    }

    void update() override {
        if (nextScene){
            if (currentScene){
                currentScene->exit();
            }
            currentScene=std::move(nextScene);
            currentScene->enter();
            LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
            if (log){
                log->write(NOTIFICATION,"A new scene has been loaded into scene system");
            }
        }

        if (currentScene){
            currentScene->update();
        }
    }
    void print() override {
        if (currentScene){
            currentScene->print();
        }
    }
    void destruct() override {
        if (currentScene){
            currentScene->exit();
        }
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            log->write(NOTIFICATION,"Scene system is destructed");
        }
    }
};
#endif