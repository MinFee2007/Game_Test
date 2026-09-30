#ifndef SYSTEM_UI_H
#define SYSTEM_UI_H

#include <vector>
#include <unordered_map>

#include "i_subsystem.h"
#include "system_ecs.h"

class GUISystem:public ISubSystem{
    private:
    std::unordered_map<std::string,Entity*> GUInodes;
    public:
    void init() override {}
    void update() override {}
    void destruct() override {
        std::cout<<"UI system is destructed\n";
    }
    Entity* addNodes(std::string name,Entity& e){
        auto it=GUInodes.find(name);
        if (it!=GUInodes.end()){
            std::cout<<"Warning: GUI node "<<name<<" already exists\n";
            return &e;
        }
        GUInodes[name]=&e;
        return &e;
    }
    Entity* getNodes(std::string name){
        auto it=GUInodes.find(name);
        if (it!=GUInodes.end()){
            return it->second;
        }
        std::cout<<"Error: Can't find GUI node "<<name<<"\n";
        return nullptr;
    }
};
#endif