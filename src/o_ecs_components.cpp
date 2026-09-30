#include "o_ecs_components.h"
SpriteComponent::SpriteComponent(std::string filepath){
    ResourceSystem* rs=AllSystem::getInstance().getSubSystem<ResourceSystem>();
    if (rs){
        texture=rs->loadTexture(filepath);
    }
}
SpriteComponent::SpriteComponent(std::string filepath,float xcut,float ycut,float w,float h,float turn_angle):
    srcrect({xcut,ycut,w,h}),dstrect({0,0,w,h}){
    texture=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadTexture(filepath);
    }
SpriteComponent::SpriteComponent(std::string filepath,float xcut,float ycut,float wcut,float hcut,float x,float y,float w,float h,float turn_angle):
    srcrect({xcut,ycut,wcut,hcut}),dstrect({x,y,w,h}){
    ResourceSystem* rs=AllSystem::getInstance().getSubSystem<ResourceSystem>();
    if (rs){
        texture=rs->loadTexture(filepath);
    }
}
SpriteComponent::~SpriteComponent(){
    SDL_DestroyTexture(texture);
}
void SpriteComponent::setTexture(std::string filepath){
    ResourceSystem* rs=AllSystem::getInstance().getSubSystem<ResourceSystem>();
    if (rs){
        texture=rs->loadTexture(filepath);
    }
}
void SpriteComponent::print(){
    SDL_Renderer* r=AllSystem::getInstance().getRenderer();
    if (r){
        SDL_RenderTexture(r,texture,&srcrect,&dstrect);
    }
}
PositionComponent::PositionComponent():position(0.0f,0.0f){}
PositionComponent::PositionComponent(float x,float y):position(x,y){}
VelocityComponent::VelocityComponent():direction(0.0f,0.0f),velocity(0.0f),acceleration(0.0f){}
VelocityComponent::VelocityComponent(float xdir,float ydir):direction(xdir,ydir),velocity(0.0f),acceleration(0.0f){
    direction.normalize();
}
VelocityComponent::VelocityComponent(float xdir,float ydir,float spd):direction(xdir,ydir),velocity(spd),acceleration(0.0f){
    direction.normalize();
}
VelocityComponent::VelocityComponent(float xdir,float ydir,float spd,float a):direction(xdir,ydir),velocity(spd),acceleration(a){
    direction.normalize();
}
TextBoxComponent::TextBoxComponent(std::string initial_text,std::string fontpath,SDL_Color color,float size,float x,float y,float w,float p):
    text(initial_text),
    font(nullptr),
    color(color),
    texture(nullptr),
    isDirty(true),
    fontsize(size),
    width(w),
    padding(p)
{

    font=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadFont(fontpath,size);
    dstrect.x=x;
    dstrect.y=y;
}
TextBoxComponent::~TextBoxComponent(){
    SDL_DestroyTexture(texture);
}
void TextBoxComponent::setFont(std::string fontpath,float size){
    ResourceSystem* rs=AllSystem::getInstance().getSubSystem<ResourceSystem>();
    if (rs){
        font=rs->loadFont(fontpath,size);
        isDirty=true;
    }
}
void TextBoxComponent::setText(std::string newtext){
    text=newtext;
    isDirty=true;
}
void TextBoxComponent::update(){
    if (!isDirty){
        return;
    }
    if (texture){
        SDL_DestroyTexture(texture);
        texture=nullptr;
    }
    if (text.empty()||!font){
        isDirty=false;
        return;
    }
    int wraplength=static_cast<int>(width-2*padding);
    if (wraplength<=0){
        wraplength=1;
    }
    SDL_Surface* surf=TTF_RenderText_Blended_Wrapped(font,text.c_str(),0,color,wraplength);
    if (surf){
        SDL_Renderer* renderer=AllSystem::getInstance().getRenderer();
        if (renderer){
            texture=SDL_CreateTextureFromSurface(renderer,surf);
            dstrect.w=static_cast<float>(surf->w)+2*padding;
            dstrect.h=static_cast<float>(surf->h)+2*padding;
        }
        SDL_DestroySurface(surf);
    }
    isDirty=false;
}
void TextBoxComponent::print(){
    SDL_Renderer* r=AllSystem::getInstance().getRenderer();
    if (!r){
        return;
    }
    SDL_RenderTexture(r,texture,NULL,&dstrect);
}
ColliderComponent::ColliderComponent():colliderect({0,0,0,0}){}
ColliderComponent::ColliderComponent(float x,float y,float w,float h):colliderect({x,y,w,h}){}
TransformComponent::TransformComponent(float sc):scale(sc){
    
}
ButtonType1Component::ButtonType1Component(std::string filepath1,std::string filepath2,float x,float y,float w,float h):dstrect({x,y,w,h}),pre_active(false),active(false){
    ResourceSystem* rs=AllSystem::getInstance().getSubSystem<ResourceSystem>();
    if (rs){
        texture1=rs->loadTexture(filepath1);
        if (filepath2!="NULL"){
            texture2=rs->loadTexture(filepath2);
        }
        else {
            texture2=texture1;
        }
        if ((!texture2)||(!texture1)){
            std::cout<<"Warning: Couldn't load textures for button component\n";
        }
        texture=texture1;
    }
}
void ButtonType1Component::update(){
    EventSystem* es=AllSystem::getInstance().getSubSystem<EventSystem>();
    if (!es){
        std::cout<<"Warning: can't find event system\n";
        return;
    }
    for (SDL_Event e:es->getEvent()){
        if (pre_active==false&&e.type==SDL_EVENT_MOUSE_BUTTON_DOWN&&e.button.button==SDL_BUTTON_LEFT){
            float x=e.button.x;
            float y=e.button.y;
            if ((x>=dstrect.x&&x<=dstrect.x+dstrect.w)&&(y>=dstrect.y&&y<=dstrect.y+dstrect.h)){
                pre_active=true;
                texture=texture2;
            }
            else {
                pre_active=false;
            }
            
        }
        else if (pre_active==true&&e.type==SDL_EVENT_MOUSE_BUTTON_UP&&e.button.button==SDL_BUTTON_LEFT){
            active=true;
            pre_active=false;
            texture=texture1;
        }
    }
}
void ButtonType1Component::print(){
    SDL_Renderer* r=AllSystem::getInstance().getRenderer();
    if (r){
        SDL_RenderTexture(r,texture,NULL,&dstrect);
    }
}