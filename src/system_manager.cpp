#include "system_manager.h"
void ManagerSystem::init(){
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (log){
        log->write(NOTIFICATION,"Manager system is initialized successfully");
    }
}
void ManagerSystem::update(){
    EventSystem* sys_event=AllSystem::getInstance().getSubSystem<EventSystem>();
    SceneSystem* sys_scene=AllSystem::getInstance().getSubSystem<SceneSystem>();
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (!sys_scene){
        if (log){
            log->write(ERROR,"Unable to get scene system");
        }
        return;
    }
    if (!sys_event){
        if (log){
            log->write(ERROR,"Unable to get event system");
        }
        return;
    }
    if (AllSystem::getInstance().getChange()){
        AllSystem::getInstance().setChange(false);
        if (AllSystem::getInstance().getState()==MENU_MAIN){
            // SceneMainMenu* scene=new SceneMainMenu();
            // std::unique_ptr<IScene> sceneptr(scene); 
            // sys_scene->changeScene(std::move(sceneptr));
            sys_scene->changeScene(std::make_unique<SceneMainMenu>());
            if (log){
                log->write(NOTIFICATION,"Main menu is loaded into scene system");
            }
        }
        else {
            if (log){
                log->write(ERROR,"Unknown all system's state");
            }
        }
    }
    if (sys_event->isQuit()){
        AllSystem::getInstance().quit();
        if (log){
            log->write(NOTIFICATION,"Program is closed successfully");
        }
    }
}
void ManagerSystem::destruct(){
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (log){
        log->write(NOTIFICATION,"Manager system is destructed");
    }
}