#ifndef SYSTEM_RESOURCE_H
#define SYSTEM_RESOURCE_H

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

#include "isubsystem.h"

class ResourceSystem:public ISubSystem{
    private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string,SDL_Texture*> texturemap; // Map for textures
    std::unordered_map<std::string,TTF_Font*> fontmap; // Map for fonts
    public:
    void init() override {}
    void setRenderer(SDL_Renderer* r){
        renderer=r;
        if (!renderer){
            std::cout<<"Warning: Resource system's renderer is empty\n";
        }
    }
    SDL_Texture* loadTexture(const std::string& filepath){
        auto it=texturemap.find(filepath);
        if (it!=texturemap.end()){
            return it->second;
        }
        if (!renderer){
            std::cout<<"Error: Resource system's renderer has not been assigned yet\n";
            return nullptr;
        }
        SDL_Texture* texture=IMG_LoadTexture(renderer,filepath.c_str());
        if (!texture){
            std::cout<<"Error: Unable to load texture in resource system\n";
            return nullptr;
        }
        texturemap[filepath]=texture;
        return texture;
    }
    void unloadTexture(const std::string& filepath){
        auto it=texturemap.find(filepath);
        if (it!=texturemap.end()){
            SDL_DestroyTexture(it->second);
            texturemap.erase(it);
        }
    }
    TTF_Font* loadFont(const std::string& filepath){
        auto it=fontmap.find(filepath);
        if (it!=fontmap.end()){
            return it->second;
        }
        TTF_Font* font=TTF_OpenFont(filepath.c_str(),72.0f);
        fontmap[filepath]=font;
        return font;
    }
    void unloadFont(const std::string& filepath){
        auto it=fontmap.find(filepath);
        if (it!=fontmap.end()){
            TTF_CloseFont(it->second);
            fontmap.erase(it);
        }
    }
    void destruct() override {
        for (auto& p:texturemap){
            if (p.second!=nullptr){
                SDL_DestroyTexture(p.second);
            }
        }
        texturemap.clear();
    }
    void update() override {}
};
#endif