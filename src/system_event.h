#ifndef SYSTEM_EVENT_H
#define SYSTEM_EVENT_H

#include <vector>
#include <SDL3/SDL.h>

#include "i_subsystem.h"

class EventSystem:public ISubSystem{
    private:
    // Attributes
    SDL_Event event; // SDL_Event
    bool quitRequested=false; // Quit event flag

    const bool* currentKeyStates=nullptr; // Pointer to the current key state array
    int numKeys=0; // Number of keys in the current key state array
    std::vector<Uint8> lastKeyStates; //Key states from last frame
    
    public:
    //Getters
    SDL_Event& getEvent(){
        return event;
    }
    bool isQuit() const {
        return quitRequested;
    }
    bool isKeyHeld(SDL_Scancode key) const {
        // Check if key is being held down
        return currentKeyStates[key]!=0;
    }
    bool isKeyPressed(SDL_Scancode key) const {
        // Check if key is pressed
        return (currentKeyStates[key]!=0)&&(lastKeyStates[key]==0);
    }
    bool isKeyReleased(SDL_Scancode key) const {
        // Check if key is released
        return (currentKeyStates[key]==0)&&(lastKeyStates[key]!=0);
    }
    bool isAnyPressed() const {
        // Check if any key is pressed
        for (int keyi=0;keyi<numKeys;keyi++){
            if ((currentKeyStates[keyi]!=0)&&(lastKeyStates[keyi]==0)){
                return true;
            }
        }
        return false;
    }

    // Methods
    void init() override {
        // Initialize current key states and last key states
        currentKeyStates=SDL_GetKeyboardState(&numKeys);
        lastKeyStates.resize(numKeys,0);
    }
    void update() override{
        // Saving current key states to last key states after a frame update
        for (int i=0;i<numKeys;++i) {
            lastKeyStates[i]=currentKeyStates[i];
        }
        // Polling events
        while (SDL_PollEvent(&event)) {
            if (event.type==SDL_EVENT_QUIT) {
                quitRequested=true;
            }
        }
    }
    void destruct() override {
        std::cout<<"Event system is destructed\n";
    }
};
#endif