#ifndef SYSTEM_EVENT_H
#define SYSTEM_EVENT_H

#include <vector>
#include <SDL3/SDL.h>

#include "i_subsystem.h"
#include "system_all.h"
#include "system_log.h"

class EventSystem:public ISubSystem{
    private:
    // Attributes
    std::vector<SDL_Event> frameEvents; // Events in a frame
    bool quitRequested=false; // Quit event flag

    const bool* currentKeyStates=nullptr; // Pointer to the current key state array
    int numKeys=0; // Number of keys in the current key state array
    std::vector<Uint8> lastKeyStates; //Key states from last frame
    
    public:
    //Getters
    const std::vector<SDL_Event>& getEvent() const; // Get all events in the current frame
    bool isQuit() const; // Check quit event
    bool isKeyHeld(SDL_Scancode key) const; // Check if key is being held down
    bool isKeyPressed(SDL_Scancode key) const; // Check if key is pressed
    bool isKeyReleased(SDL_Scancode key) const; // Check if key is released
    bool isAnyPressed() const; // Check if any key is pressed

    // Methods
    void init() override;
    void update() override;
    void destruct() override;
};
#endif