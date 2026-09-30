#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

#include <Vector2D.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

#include "system_all.h"
#include "system_resource.h"
#include "system_event.h"
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
    SpriteComponent(std::string filepath,float xcut,float ycut,float w,float h,float turn_angle);
    SpriteComponent(std::string filepath,float xcut,float ycut,float wcut,float hcut,float x,float y,float w,float h,float turn_angle);
    ~SpriteComponent() override;
    void setTexture(std::string filepath);
    void print() override;
};
class PositionComponent:public Component{
    public:
    Vector2D position;
    PositionComponent();
    PositionComponent(float x,float y);
};
class VelocityComponent:public Component{
    public:
    Vector2D direction;
    float velocity;
    float acceleration;
    VelocityComponent();
    VelocityComponent(float xdir,float ydir);
    VelocityComponent(float xdir,float ydir,float spd);
    VelocityComponent(float xdir,float ydir,float spd,float a);
};
class TextBoxComponent:public Component {
    public:
    std::string text;
    TTF_Font* font;
    SDL_Color color;
    SDL_Texture* texture;
    SDL_FRect dstrect;
    float fontsize;
    float width;
    float padding;
    bool isDirty; // Changing flag
    TextBoxComponent(std::string initial_text,std::string fontpath,SDL_Color color,float size,float x,float y,float w,float p);
    ~TextBoxComponent() override;
    void setFont(std::string fontpath,float size);
    void setText(std::string newtext);
    void update() override;
    void print() override;
};
class ColliderComponent:public Component{
    public:
    SDL_FRect colliderect;
    ColliderComponent();
    ColliderComponent(float x,float y,float w,float h);
};
class TransformComponent:public Component{
    public:
    float scale=1.0f;
    TransformComponent::TransformComponent(float sc);
};
class ButtonComponent:public Component{
    public:
    SDL_FRect dstrect;
    SDL_Texture* texture1;
    SDL_Texture* texture2;
    SDL_Texture* texture;
    bool active1;
    bool active2;
    ButtonComponent::ButtonComponent(std::string filepath1,std::string filepath2,float x,float y,float w,float h);
    void update() override;
    void print() override;
};
class AnimationComponent;
class InputComponent;
class HealthComponent;
class AIBrainComponent;
#endif