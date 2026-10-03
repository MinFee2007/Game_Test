#include "o_scenes.h"
SceneMainMenu::SceneMainMenu():state("entering"){
}
void SceneMainMenu::enter(){
    EntityComponentSystem* ecs=AllSystem::getInstance().getSubSystem<EntityComponentSystem>();
    float screenw=static_cast<float>(AllSystem::getInstance().getScreenWidth());
    float screenh=static_cast<float>(AllSystem::getInstance().getScreenHeight());
    if (ecs){
        Entity& background=ecs->addEntity();
        background.addComponent<SpriteComponent>("assets/pictures/bg_mainmenu.png",SDL_FRect{0,0,screenw,screenh},0.0f);
        entities["background"]=&background;
        Entity& gametitle=ecs->addEntity();
        gametitle.addComponent<TextBoxComponent>("Testing","assets/fonts/kvn-97.ttf",SDL_Color{190,190,190,255},36.0f,(screenw-910.0f)/2.0f,screenh*1/10,900.0f,10.0f);
        entities["gametitle"]=&gametitle;
        std::cout<<"Main menu is initialized\n";
    }
    else {
        std::cout<<"Error: Couldn't find entity component system\n";
    }
}
void SceneMainMenu::update(){
    for (Entity* e:AllSystem::getInstance().getSubSystem<EntityComponentSystem>()->getGroup(0)){
        e->update();
    }
    if (state=="entering"){
        
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