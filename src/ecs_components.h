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
    private:
    SDL_Texture* texture;
    SDL_FRect srcrect;
    SDL_FRect dstrect;
    float angle;
    public:
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
};
class PositionComponent:public Component{
    private:
    Vector2D position;
    public:
    PositionComponent():position(0.0f,0.0f){}
    PositionComponent(float x,float y):position(x,y){}
};
class VelocityComponent:public Component{
    private:
    Vector2D direction;
    float velocity;
    float acceleration;
    public:
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
private:
    std::string text;
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* texture;
    SDL_FRect dstrect;
    bool isDirty; // Cờ đánh dấu khi text bị thay đổi,cần vẽ lại texture

public:
    TextBoxComponent(std::string initial_text,std::string fontpath,SDL_Color color,float x,float y)
        :text(initial_text),font(font),color(color),texture(nullptr),isDirty(true){
        font=AllSystem::getInstance().getSubSystem<ResourceSystem>()->loadFont(fontpath);
        dstrect.x=x;
        dstrect.y=y;
    }
    void setText(const std::string& new_text) {
        if (text!=new_text) {
            text=new_text;
            isDirty=true; // Yêu cầu render lại texture ở frame tiếp theo
        }
    }

    void update() override {
        // Nếu nội dung thay đổi, giải phóng texture cũ và tạo texture mới
        if (isDirty&&font!=nullptr){
            if (texture!=nullptr){
                SDL_DestroyTexture(texture);
            }
            // Lấy Renderer từ AllSystem (Singleton)
            SDL_Renderer* renderer=AllSystem::getInstance().getRenderer();
            // Tạo Surface và Texture từ text
            SDL_Surface* surface=TTF_RenderText_Solid(font,text.c_str(),text.length(),color);
            if (surface){
                texture=SDL_CreateTextureFromSurface(renderer,surface);
                dstrect.w=surface->w;
                dstrect.h=surface->h;
                SDL_DestroySurface(surface);
            }
            isDirty=false;
        }
    }
    
    SDL_Texture* getTexture() const { return texture; }
    SDL_FRect getDestRect() const { return dstrect; }

    ~TextBoxComponent() override {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
};
class ColliderComponent:public Component{
    private:
    SDL_FRect colliderect;
    public:
    ColliderComponent():colliderect({0,0,0,0}){}
    ColliderComponent(float x,float y,float w,float h):colliderect({x,y,w,h}){}
};
class TransformComponent:public Component{

};
class AnimationComponent;
class InputComponent;
class HealthComponent;
class AIBrainComponent;
#endif