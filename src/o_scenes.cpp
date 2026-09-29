#include "o_scenes.h"
SceneMainMenu::SceneMainMenu():state("entering"){
    EntityComponentSystem* ecs=AllSystem::getInstance().getSubSystem<EntityComponentSystem>();
    if (ecs){
        Entity& gametitle=ecs->addEntity();
        gametitle.addComponent<TextBoxComponent>("You are gay","graphics/fonts/DL-ThuPhap.ttf",SDL_Color{20,20,240,255},42.0f,200.0f,200.0f,700.0f,10.0f);
        gametitle.addGroup(0);
        std::cout<<"Main menu is initialized\n";
    }
    else {
        std::cout<<"Error: Couldn't find entity component system\n";
    }
    
}
void SceneMainMenu::enter(){
    
}
void SceneMainMenu::update(){
    for (Entity* e:AllSystem::getInstance().getSubSystem<EntityComponentSystem>()->getGroup(0)){
        e->update();
    }
}
void SceneMainMenu::print(){
    for (Entity* e:AllSystem::getInstance().getSubSystem<EntityComponentSystem>()->getGroup(0)){
        e->print();
    }
}
void SceneMainMenu::exit(){
    for (Entity* e:AllSystem::getInstance().getSubSystem<EntityComponentSystem>()->getGroup(0)){
        e->delGroup(0);
    }
}