#ifndef SYSTEM_TIME_H
#define SYSTEM_TIME_H

#include <string>
#include <fstream>
#include <SDL3/SDL.h>

#include "i_subsystem.h"
#include "system_all.h"

class TimeSystem:public ISubSystem{
    private:
    // Attributes
    Uint64 lastTime=0; // Last record time
    float deltaTime=0.0f; // Time between two frames
    float timeScale=1.0f; // Time scale factor
    float targetFrameTime; // Time per frame in miliseconds
    public:
    void init() override;
    void update() override;
    void destruct();
    // Getters
    float getDeltaTime() const;
    float getUnscaledDeltaTime() const;
    void setTimeScale(float scale);
    std::string getDate();
    std::string getTime();
};
#endif