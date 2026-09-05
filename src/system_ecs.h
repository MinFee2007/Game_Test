#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

#include "isubsystem.h"

//pre-init
class Entity;
class Component;
class EntityComponentSystem;

using ComponentID=std::size_t;
using Group=std::size_t;

//Grant new ID if the component is new
inline ComponentID GetNewComponentTypeID(){
    static ComponentID lastid=0u;
    return lastid++;
}

//Get or grant new ID of a component depend of whether it has already existed or not
template<typename T> inline ComponentID GetComponentTypeID() noexcept {
    static ComponentID TypeID=GetNewComponentTypeID();
    return TypeID;
}

constexpr std::size_t maxComponent=32;
constexpr std::size_t maxGroups=32;

using ComponentBitSet=std::bitset<maxComponent>;
using GroupBitSet=std::bitset<maxGroups>;
using ComponentArray=std::array<Component*,maxComponent>;
using GroupArray=std::array<std::vector<Entity*>,maxGroups>;

//class Component
class Component{
    protected:
    Entity* entity;
    protected:
    virtual Entity* getEntity() const {
        return entity;
    }
    public:    
    virtual void init(){};
    virtual void update(){};
    virtual void print(){};
    virtual ~Component()=default;
};

//class Entity
class Entity{
    private:
    EntityComponentSystem& manager;
    bool active=true;
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentarray;
    ComponentBitSet componentbitset;
    GroupBitSet groupbitset;
    public:
    Entity(EntityComponentSystem& mManager);
    void update();
    void print();
    bool isActive();
    void destroy();
    bool hasGroup(Group mGroup);
    void addGroup(Group mGroup);
    void delGroup(Group mGroup);
    template<typename T> bool hasComponent() const {
        return componentbitset[GetComponentTypeID<T>()];
    }
    template<typename T,typename... TArgs> T& addComponent(TArgs&&... args){
        T* c=new T(std::forward<TArgs>(args)...);
        c->entity=this;
        std::unique_ptr<Component> uPtr(c);
        components.emplace_back(std::move(uPtr));
        componentarray[GetComponentTypeID<T>()]=c;
        componentbitset[GetComponentTypeID<T>()]=true;
        c->init();
        return *c;
    }
    template<typename T> T& getComponent() const {
        auto ptr(componentarray[GetComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

//class EntityComponentSystem
class EntityComponentSystem:public ISubSystem{
    private:
    std::vector<std::unique_ptr<Entity>> entities;
    GroupArray groupedentities;
    public:
    void init() override;
    void update() override;
    void print();
    void refresh();
    void addToGroup(Entity* mEntity, Group mGroup);
    std::vector<Entity*>& getGroup(Group mGroup);
    Entity& addEntity();
    void destruct() override;
};
#endif