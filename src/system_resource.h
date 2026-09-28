#ifndef SYSTEM_RESOURCE_H
#define SYSTEM_RESOURCE_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

#include "i_subsystem.h"

#include "system_all.h"

class ResourceSystem:public ISubSystem{
    private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string,SDL_Texture*> texturemap; // Map for textures
    std::unordered_map<std::string,TTF_Font*> fontmap; // Map for fonts
    public:
    void init() override;
    void setRenderer(SDL_Renderer* r);
    SDL_Texture* loadTexture(const std::string& filepath);
    void unloadTexture(const std::string& filepath);
    TTF_Font* loadFont(const std::string& filepath);
    void unloadFont(const std::string& filepath);
    void destruct() override;
    void update() override;
};
#endif