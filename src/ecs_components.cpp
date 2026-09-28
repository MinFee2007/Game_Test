#include "ecs_components.h"
SpriteComponent::SpriteComponent(std::string filepath){
    texture=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadTexture(filepath);
}
SpriteComponent::SpriteComponent(std::string filepath,float xcut,float ycut,float w,float h,float turn_angle):
    srcrect({xcut,ycut,w,h}),dstrect({0,0,w,h}){
    texture=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadTexture(filepath);
    }
SpriteComponent::SpriteComponent(std::string filepath,float xcut,float ycut,float wcut,float hcut,float x,float y,float w,float h,float turn_angle):
    srcrect({xcut,ycut,wcut,hcut}),dstrect({x,y,w,h}){
    texture=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadTexture(filepath);
    }
SpriteComponent::~SpriteComponent(){
    SDL_DestroyTexture(texture);
}
void SpriteComponent::setTexture(std::string filepath){
    texture=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadTexture(filepath);
}
PositionComponent::PositionComponent():position(0.0f,0.0f){}
PositionComponent::PositionComponent(float x,float y):position(x,y){}
VelocityComponent::VelocityComponent():direction(0.0f,0.0f),velocity(0.0f),acceleration(0.0f){}
VelocityComponent::VelocityComponent(float xdir,float ydir):direction(ydir,xdir),velocity(0.0f),acceleration(0.0f){
    direction.normalize();
}
VelocityComponent::VelocityComponent(float xdir,float ydir,float spd):direction(xdir,ydir),velocity(spd),acceleration(0.0f){
    direction.normalize();
}
VelocityComponent::VelocityComponent(float xdir,float ydir,float spd,float a):direction(xdir,ydir),velocity(spd),acceleration(a){
    direction.normalize();
}
TextBoxComponent::TextBoxComponent(std::string initial_text,std::string fontpath,SDL_Color color,float x,float y,float w):
    text(initial_text),
    font(font),
    color(color),
    texture(nullptr),
    isDirty(true),
    width(w)
{
    font=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadFont(fontpath);
    dstrect.x=x;
    dstrect.y=y;
}
TextBoxComponent::~TextBoxComponent(){
    SDL_DestroyTexture(texture);
}
void TextBoxComponent::setFont(std::string fontpath){
    font=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadFont(fontpath);
    isDirty=true;
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
ColliderComponent::ColliderComponent():colliderect({0,0,0,0}){}
ColliderComponent::ColliderComponent(float x,float y,float w,float h):colliderect({x,y,w,h}){}