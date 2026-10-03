#include "system_manager.h"
void ManagerSystem::init(){}
void ManagerSystem::update(){
    EventSystem* sys_event=AllSystem::getInstance().getSubSystem<EventSystem>();
    SceneSystem* sys_scene=AllSystem::getInstance().getSubSystem<SceneSystem>();
    if (!sys_scene){
        std::cout<<"Error: Unable to get scene system\n";
        return;
    }
    if (!sys_event){
        std::cout<<"Error: Unable to get event system\n";
        return;
    }
    if (AllSystem::getInstance().getChange()){
        AllSystem::getInstance().setChange(false);
        if (AllSystem::getInstance().getState()==MENU_MAIN){
            // SceneMainMenu* scene=new SceneMainMenu();
            // std::unique_ptr<IScene> sceneptr(scene); 
            // sys_scene->changeScene(std::move(sceneptr));
            sys_scene->changeScene(std::make_unique<SceneMainMenu>());
            std::cout<<"Main menu is loaded into scene system\n";
        }
        else {
            std::cout<<"Error: Unknown all system's state\n";
        }
    }
    if (sys_event->isQuit()){
        AllSystem::getInstance().quit();
        std::cout<<"Program's closed successfully\n";
    }
}
void ManagerSystem::destruct(){
    std::cout<<"Manager system is destructed\n";
}