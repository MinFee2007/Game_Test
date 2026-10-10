#include "system_time.h"
void TimeSystem::init(){
    float targetFPS=AllSystem::getInstance().getTargetFPS(); // Frames per second
    targetFrameTime=(targetFPS>0)?(1000.0f/static_cast<float>(targetFPS)):16.666f; // Time per frame (ms/f)
    lastTime=SDL_GetTicksNS(); // Record initial time in nanoseconds
    SDL_Time currentTick;
    if (!SDL_GetCurrentTime(&currentTick)){ // Get the real current tick from UTC
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            log->write(WARNING,"Time system is unable to get current tick");
        }
        return;
    }
    if (!SDL_TimeToDateTime(currentTick,&dateTime,true)){ // Transforming real current tick to real date and time
        LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
        if (log){
            log->write(WARNING,"Time system is unable to get current date & time");
        }
        return;
    }
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (log){
        log->write(NOTIFICATION,"Time system is initialized successfully");
    }
}
void TimeSystem::update(){
    Uint64 currentTime=SDL_GetTicksNS(); // Record current time in nanoseconds
    float elapseTime=static_cast<float>(currentTime-lastTime)/1'000'000.0f; // Calculate elapsed time in miliseconds
    if (elapseTime<targetFrameTime){ // Check if the elapsed time is long enough for a new frame update
        SDL_Delay(static_cast<Uint64>(targetFrameTime-elapseTime)); // Delay
        currentTime=SDL_GetTicksNS(); // Get the real time tick in nanoseconds after the delay
    }
    deltaTime=static_cast<float>(currentTime-lastTime)/1'000'000'000.0f; // Calcute delta time in seconds
    lastTime=currentTime; // Update last time to current time for next frame
    if (deltaTime>0.1f){
        deltaTime=0.1f; // Delta time capping
    }
}
void TimeSystem::destruct(){
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (log){
        log->write(NOTIFICATION,"Time system is destructed");
    }
}
// Getters
float TimeSystem::getDeltaTime() const {
    return deltaTime*timeScale; // Return scaled delta time
}
float TimeSystem::getUnscaledDeltaTime() const { 
    return deltaTime; // Return unscaled delta time (for UI)
}
void TimeSystem::setTimeScale(float scale){
    timeScale=scale; // Set time scale factor
}
SDL_DateTime TimeSystem::getDateTime(){
    SDL_Time currentTick;
    if (SDL_GetCurrentTime(&currentTick)){
        if (SDL_TimeToDateTime(currentTick,&dateTime,true)){
            return dateTime;
        }
    }
    std::cerr<<"Time system is unable to get date & time, returned last call instead";
    return dateTime;
}