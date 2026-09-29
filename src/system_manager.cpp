#include "system_manager.h"
ManagerSystem::ManagerSystem():isChange(true){}
bool ManagerSystem::getChange() const {
    return isChange;
}
void ManagerSystem::toggleChange(){
    isChange=!isChange;
}
void ManagerSystem::init(){
    isChange=true;
}
void ManagerSystem::setChange(bool change){
    isChange=change;
}
void ManagerSystem::update(){
    EventSystem* sys_event=AllSystem::getInstance().getSubSystem<EventSystem>();
    SceneSystem* sys_scene=AllSystem::getInstance().getSubSystem<SceneSystem>();
    if (isChange){
        isChange=false;
        if (AllSystem::getInstance().getState()=="menu_main"){
            if (sys_scene){
                // SceneMainMenu* scene=new SceneMainMenu();
                // std::unique_ptr<IScene> sceneptr(scene); 
                // sys_scene->changeScene(std::move(sceneptr));
                sys_scene->changeScene(std::make_unique<SceneMainMenu>());
                std::cout<<"Main menu is loaded into scene system\n";
            }
            else {
                std::cout<<"Error: Unable to get scene system\n";
            }
        }
        else {
            std::cout<<"Error: Unknown all system's state\n";
        }
    }
    if (sys_event){
        if (sys_event->isQuit()){
            AllSystem::getInstance().quit();
            std::cout<<"Program's closed successfully\n";
        }
    }
}
void ManagerSystem::destruct(){
    std::cout<<"Manager system is destructed\n";
}