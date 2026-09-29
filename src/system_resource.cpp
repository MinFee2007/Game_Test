#include "system_resource.h"
void ResourceSystem::init(){
    renderer=AllSystem::getInstance().getRenderer();
    if (!renderer){
        std::cout<<"Warning: All system's renderer is empty\n";
    }
}
void ResourceSystem::setRenderer(SDL_Renderer* r){
    renderer=r;
    if (!renderer){
        std::cout<<"Warning: Resource system's renderer is empty\n";
    }
}
SDL_Texture* ResourceSystem::loadTexture(const std::string& filepath){
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
        std::cout<<"Error: Unable to load texture "<<filepath<<" into resource system\n";
        return nullptr;
    }
    texturemap[filepath]=texture;
    std::cout<<"Texture "<<filepath<<" is loaded into resource system\n";
    return texture;
}
void ResourceSystem::unloadTexture(const std::string& filepath){
    auto it=texturemap.find(filepath);
    if (it!=texturemap.end()){
        SDL_DestroyTexture(it->second);
        texturemap.erase(it);
        std::cout<<"Texture "<<filepath<<" is unloaded from resource system\n";
    }
}
TTF_Font* ResourceSystem::loadFont(const std::string& filepath,float ptsize){
    std::string key=filepath+"_"+std::to_string(static_cast<int>(ptsize));
    auto it=fontmap.find(filepath);
    if (it!=fontmap.end()){
        return it->second;
    }
    TTF_Font* font=TTF_OpenFont(filepath.c_str(),ptsize);
    if (!font){
        std::cout<<"Error: Unable to load font "<<filepath<<" with size "<<ptsize<<" into resource system\n";
        return nullptr;
    }
    fontmap[key]=font;
    std::cout<<"Font "<<filepath<<" with size "<<ptsize<<" is loaded into resource system\n";
    return font;
}
void ResourceSystem::unloadFont(const std::string& filepath,float ptsize){
    std::string key=filepath+"_"+std::to_string(static_cast<int>(ptsize));
    auto it=fontmap.find(key);
    if (it!=fontmap.end()){
        TTF_CloseFont(it->second);
        fontmap.erase(it);
        std::cout<<"Font "<<filepath<<" with size "<<ptsize<<" is unloaded from resource system\n";
    }
}
void ResourceSystem::destruct(){
    for (auto& p:texturemap){
        if (p.second!=nullptr){
            SDL_DestroyTexture(p.second);
        }
    }
    texturemap.clear();
    std::cout<<"Resource system is destructed\n";
}
void ResourceSystem::update(){}