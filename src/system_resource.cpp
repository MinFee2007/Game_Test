#include "system_resource.h"
void ResourceSystem::init(){
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    renderer=AllSystem::getInstance().getRenderer();
    if (!renderer){
        if (log){
            log->write(ERROR,"All system's renderer is empty");
            log->write(NOTIFICATION,"Time system is initialized without renderer");
        }
        return;
    }
    if (log){
        log->write(NOTIFICATION,"Resource system is initialized successfully");
    }
}
void ResourceSystem::setRenderer(SDL_Renderer* r){
    renderer=r;
    if (!renderer){
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            log->write(WARNING,"Resource system's renderer is empty");
        }
    }
}
SDL_Texture* ResourceSystem::loadTexture(const std::string& filepath){
    auto it=texturemap.find(filepath);
    if (it!=texturemap.end()){
        return it->second;
    }
    if (!renderer){
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            log->write(ERROR,"Resource system's renderer has not been assigned yet");
        }
        return nullptr;
    }
    SDL_Texture* texture=IMG_LoadTexture(renderer,filepath.c_str());
    if (!texture){
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            std::string msg="Unable to load texture "+filepath+" into resource system";
            log->write(ERROR,msg);
        }
        return nullptr;
    }
    texturemap[filepath]=texture;
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (log){
        std::string msg="Texture "+filepath+" is loaded into resource system";
        log->write(NOTIFICATION,msg);
    }
    return texture;
}
void ResourceSystem::unloadTexture(const std::string& filepath){
    auto it=texturemap.find(filepath);
    if (it!=texturemap.end()){
        SDL_DestroyTexture(it->second);
        texturemap.erase(it);
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            std::string msg="Texture "+filepath+" is unloaded from resource system";
            log->write(NOTIFICATION,msg);
        }
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
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            std::string msg="Unable to load font "+filepath+" with size "+std::to_string(static_cast<int>(ptsize))+" into resource system";
            log->write(ERROR,msg);
        }
        return nullptr;
    }
    fontmap[key]=font;
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (log){
        std::string msg="Font "+filepath+" with size "+std::to_string(static_cast<int>(ptsize))+" is loaded into resource system";
        log->write(NOTIFICATION,msg);
    }
    return font;
}
void ResourceSystem::unloadFont(const std::string& filepath,float ptsize){
    std::string key=filepath+"_"+std::to_string(static_cast<int>(ptsize));
    auto it=fontmap.find(key);
    if (it!=fontmap.end()){
        TTF_CloseFont(it->second);
        fontmap.erase(it);
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            std::string msg="Font "+filepath+" with size "+std::to_string(static_cast<int>(ptsize))+" is unloaded from resource system";
            log->write(NOTIFICATION,msg);
        }
    }
}
void ResourceSystem::destruct(){
    for (auto& p:texturemap){
        if (p.second!=nullptr){
            SDL_DestroyTexture(p.second);
        }
    }
    texturemap.clear();
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (log){
        log->write(NOTIFICATION,"Resource system is destructed");
    }
}
void ResourceSystem::update(){}