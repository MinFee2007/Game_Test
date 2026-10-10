#include "system_event.h"
const std::vector<SDL_Event>& EventSystem::getEvent() const {
    return frameEvents;
}
bool EventSystem::isQuit() const {
    return quitRequested;
}
bool EventSystem::isKeyHeld(SDL_Scancode key) const {
    return currentKeyStates[key]!=0;
}
bool EventSystem::isKeyPressed(SDL_Scancode key) const {
    return (currentKeyStates[key]!=0)&&(lastKeyStates[key]==0);
}
bool EventSystem::isKeyReleased(SDL_Scancode key) const {
    return (currentKeyStates[key]==0)&&(lastKeyStates[key]!=0);
}
bool EventSystem::isAnyPressed() const {
    for (int keyi=0;keyi<numKeys;keyi++){
        if ((currentKeyStates[keyi]!=0)&&(lastKeyStates[keyi]==0)){
            return true;
        }
    }
    return false;
}

// Methods
void EventSystem::init(){
    // Initialize current key states and last key states
    currentKeyStates=SDL_GetKeyboardState(&numKeys);
    lastKeyStates.resize(numKeys,0);
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (log){
        log->write(NOTIFICATION,"Event system is initialized successfully");
    }
}
void EventSystem::update(){
    // Saving current key states to last key states after a frame update
    for (int i=0;i<numKeys;++i) {
        lastKeyStates[i]=currentKeyStates[i];
    }
    // Polling events
    frameEvents.clear();
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        frameEvents.push_back(event);
        if (event.type==SDL_EVENT_QUIT) {
            quitRequested=true;
        }
    }
}
void EventSystem::destruct(){
    LogSystem* log=AllSystem::getInstance().getSubSystem<LogSystem>();
    if (log){
        log->write(NOTIFICATION,"Event system is destructed");
    }
}