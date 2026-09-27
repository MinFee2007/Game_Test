#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <Vector2D.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>

#include "system_all.h"
#include "system_ecs.h"

class PlayerTag:public Component{};
class EnemyTag:public Component{};

class SpriteComponent:public Component{
    public:
    SDL_Texture* texture;
    SDL_FRect srcrect;
    SDL_FRect dstrect;
    float angle;
    SpriteComponent(std::string filepath);
    SpriteComponent(
    std::string filepath,
    float xcut,float ycut,float w,float h,float turn_angle):
        srcrect({xcut,ycut,w,h}),
        dstrect({0,0,w,h}){
        texture=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadTexture(filepath);
    }
    SpriteComponent(
    std::string filepath,
    float xcut,float ycut,float wcut,float hcut,
    float x,float y,float w,float h,
    float turn_angle):
        srcrect({xcut,ycut,wcut,hcut}),
        dstrect({x,y,w,h}){
        texture=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadTexture(filepath);
    }
    ~SpriteComponent() override {
        SDL_DestroyTexture(texture);
    }
    void setTexture(std::string filepath){
        texture=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadTexture(filepath);
    }
};
class PositionComponent:public Component{
    public:
    Vector2D position;
    PositionComponent():position(0.0f,0.0f){}
    PositionComponent(float x,float y):position(x,y){}
};
class VelocityComponent:public Component{
    public:
    Vector2D direction;
    float velocity;
    float acceleration;
    VelocityComponent():direction(0.0f,0.0f),velocity(0.0f),acceleration(0.0f){}
    VelocityComponent(float xdir,float ydir):direction(ydir,xdir),velocity(0.0f),acceleration(0.0f){
        direction.normalize();
    }
    VelocityComponent(float xdir,float ydir,float spd):direction(xdir,ydir),velocity(spd),acceleration(0.0f){
        direction.normalize();
    }
    VelocityComponent(float xdir,float ydir,float spd,float a):direction(xdir,ydir),velocity(spd),acceleration(a){
        direction.normalize();
    }
};
class TextBoxComponent:public Component {
    public:
    std::string text;
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* texture;
    SDL_FRect dstrect;
    float width;
    float padding;
    bool isDirty; // Changing flag
    TextBoxComponent(std::string initial_text,std::string fontpath,SDL_Color color,float x,float y,float w):
        text(initial_text),
        font(font),
        color(color),
        texture(nullptr),
        isDirty(true),
        width(w){
        font=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadFont(fontpath);
        dstrect.x=x;
        dstrect.y=y;
    }
    ~TextBoxComponent() override {
        SDL_DestroyTexture(texture);
    }
    void setFont(std::string fontpath){
        font=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadFont(fontpath);
        isDirty=true;
    }
    void setText(std::string newtext){
        text=newtext;
        isDirty=true;
    }
    void update() override {
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
};
class ColliderComponent:public Component{
    public:
    SDL_FRect colliderect;
    ColliderComponent():colliderect({0,0,0,0}){}
    ColliderComponent(float x,float y,float w,float h):colliderect({x,y,w,h}){}
};
class TransformComponent:public Component{
    public:
    float scale=1.0f;
};
class AnimationComponent;
class InputComponent;
class HealthComponent;
class AIBrainComponent;
#endif