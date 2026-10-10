#include "o_scenes.h"
SceneMainMenu::SceneMainMenu():state("entering"){
}
void SceneMainMenu::enter(){
    EntityComponentSystem* ecs=AllSystem::getInstance().getSubSystem<EntityComponentSystem>();
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    float screenw=static_cast<float>(AllSystem::getInstance().getScreenWidth());
    float screenh=static_cast<float>(AllSystem::getInstance().getScreenHeight());
    if (ecs){
        Entity& background=ecs->addEntity();
        background.addComponent<SpriteComponent>("assets/pictures/bg_mainmenu.png",SDL_FRect{0,0,screenw,screenh},0.0f);
        entities["background"]=&background;
        Entity& gametitle=ecs->addEntity();
        gametitle.addComponent<TextBoxComponent>("Testing","assets/fonts/kvn-97.ttf",SDL_Color{190,190,190,255},36.0f,(screenw-910.0f)/2.0f,screenh*1/10,900.0f,10.0f);
        entities["gametitle"]=&gametitle;
        Entity& button1=ecs->addEntity();
        button1.addComponent<ButtonType1Component>("assets/pictures/1x1_button.png","assets/pictures/1x1_button_pressed.png",SDL_FRect{200.0f,200.0f,200.0f,200.0f});
        entities["button1"]=&button1;
        if (log){
            log->write(NOTIFICATION,"Main menu is initialized");
        }
    }
    else {
        if (log){
            log->write(ERROR,"Main menu is unable to find entity component system");
        }
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