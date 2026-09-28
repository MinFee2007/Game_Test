#include "system_manager.h"
ManagerSystem::ManagerSystem(){}
void ManagerSystem::init(){}
void ManagerSystem::update(){
    EventSystem* eventsys=AllSystem::getInstance().getSubSystem<EventSystem>();
    if (eventsys){
        if (eventsys->isQuit()){
            AllSystem::getInstance().destruct();
            SDL_Quit();
            std::cout<<"Program's closed successfully\n";
        }
    }
}
void ManagerSystem::destruct(){}