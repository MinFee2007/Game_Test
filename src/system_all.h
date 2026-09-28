#ifndef ALLSYSTEM_H
#define ALLSYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>

#include <Vector2D.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>

#include "i_subsystem.h"
#include "i_scene.h"

class AllSystem{
    private:
    // Attributes
    std::string title="Test";
    bool running=true;
    int screenwidth=1152;
    int screenheight=648;
    int target_fps=60;
    std::string state="menu_main";
    SDL_Window* window=nullptr; // SDL window
    SDL_Renderer* renderer=nullptr; // SDL renderer
    std::vector<std::unique_ptr<ISubSystem>> subsystems; // Subsystems

    // Hide constructor
    AllSystem(){}

    public:
    // Meyer's singleton
    static AllSystem& getInstance(){
        static AllSystem instance;
        return instance;}
    AllSystem(AllSystem const&)=delete;
    void operator=(AllSystem const&)=delete;

    // Getters
    int getScreenWidth() const {return screenwidth;}
    int getScreenHeight() const {return screenheight;}
    SDL_Renderer* getRenderer() const {return renderer;}

    // Methods
    template<typename T,typename...TArgs> void addSubSystem(TArgs&&... args){
        // Add a subsystem
        T* subsystem=new T(std::forward<TArgs>(args)...);
        subsystems.emplace_back(std::unique_ptr<ISubSystem>(subsystem));
    }
    template<typename T> T* getSubSystem(){
        // Get a subsystem
        for (auto& subsystem:subsystems){
            T* ptr=dynamic_cast<T*>(subsystem.get());
            if (ptr){
                return ptr;
            }
        }
        return nullptr;
    }
    template<typename T> void removeSubSystem(){
        // Remove a subsystem
        for (auto it=subsystems.begin();it!=subsystems.end();++it){
            T* ptr=dynamic_cast<T*>(it->get());
            if (ptr){
                subsystems.erase(it);
                return;
            }
        }
    }

    void quit(){
        // Quit the game loop
        running=false;
    }
    
    void init(){
        // Initialize the whole system

        // Initialize SDL3 video
        if (!SDL_Init(SDL_INIT_VIDEO)){
            std::cout<<"Error: SDL_init failed: "<<SDL_GetError()<<"\n";
        }
        // Initialize SDL3 text & font
        if (!TTF_Init()){
            std::cout<<"TTF_Init Error: "<<SDL_GetError()<<"\n";
        }

        // Create a window and renderer
        SDL_CreateWindowAndRenderer(title.c_str(),screenwidth,screenheight,0,&window,&renderer);
        if (!window){
            std::cout<<"Error: SDL_CreateWindow failed: "<<SDL_GetError()<<"\n";
        }
        if (!renderer){
            std::cout<<"Error: SDL_CreateRenderer failed: "<<SDL_GetError()<<"\n";
        }

        // Initialize subsystems
        for (auto& subsystem:subsystems){
            subsystem->init();
        }

        // Notify
        std::cout<<"All system is initialized successfully\n";
    }

    void update(){
        // Update the game loop
        for (auto& subsystem:subsystems) {
            subsystem->update();
        }
    }

    void render(){
        // Render the scene in game loop
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        //

        //
        SDL_RenderPresent(renderer);
    }

    void run(){
        // Run game loop
        while (running){
            update();
            render();
        }
    }

    void destruct(){
        // Clean up resources
        for (auto& subsystem:subsystems){
            subsystem->destruct();
        }
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }
};
#endif