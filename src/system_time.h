#ifndef SYSTEM_TIME_H
#define SYSTEM_TIME_H

#include <SDL3/SDL.h>

#include "i_subsystem.h"

class TimeSystem:public ISubSystem{
    private:
    // Attributes
    Uint64 lastTime=0; // Last record time
    float deltaTime=0.0f; // Time between two frames
    float timeScale=1.0f; // Time scale factor
    public:
    void init() override {
        lastTime=SDL_GetTicks(); // Record initial time
    }
    void update() override {
        Uint64 currentTime=SDL_GetTicks(); // Record current time
        deltaTime=(currentTime-lastTime)/1000.0f; // Calcute delta time in seconds
        lastTime=currentTime; // Update last time to current time for next frame
    }
    void destruct() override {
        std::cout<<"Time system is destructed\n";
    }
    // Getters
    float getDeltaTime() const {
        return deltaTime*timeScale; // Return scaled delta time
    }
    float getUnscaledDeltaTime() const { 
        return deltaTime; // Return unscaled delta time (for UI)
    }
    void setTimeScale(float scale){
        timeScale=scale; // Set time scale factor
    }
};
#endif