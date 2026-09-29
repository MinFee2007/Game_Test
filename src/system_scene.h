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
    void init() override {}

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
            std::cout<<"A new scene has been loaded\n";
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
        std::cout<<"Scene system is destructed\n";
    }
};
#endif