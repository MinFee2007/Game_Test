#include "system_ecs.h"
Entity::Entity(EntityComponentSystem& mManager):manager(mManager){}
void Entity::update(){
    for (auto& c:components){
        c->update();
    }
}
void Entity::print(){
    for (auto& c: components){
        c->print();
    }
}
bool Entity::isActive(){
    return active;
}
void Entity::destroy(){
    active=false;
}
bool Entity::hasGroup(Group mGroup){
    return groupbitset[mGroup];
}
void Entity::delGroup(Group mGroup){
    groupbitset[mGroup]=false;
}
//methods of class EntityComponentSystem
void EntityComponentSystem::init(){}
void EntityComponentSystem::update(){
    for (auto& e:entities){
        e->update();
    }
}
void EntityComponentSystem::print(){
    for (auto& e:entities){
        e->print();
    }
}
void EntityComponentSystem::refresh(){
    for (auto i(0u);i<maxGroups;i++){
        auto& v(groupedentities[i]);
        v.erase(
            std::remove_if(
                std::begin(v),
                std::end(v),
                [i](Entity* mEntity)
                {return !mEntity->isActive()||!mEntity->hasGroup(i);}
            ),
            std::end(v)
        );
    }
        
    entities.erase(
        std::remove_if(
            std::begin(entities),
            std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity){
                return !mEntity->isActive();
            }
        ),
        std::end(entities)
    );
}
void EntityComponentSystem::addToGroup(Entity* mEntity,Group mGroup){
    groupedentities[mGroup].emplace_back(mEntity);
}
std::vector<Entity*>& EntityComponentSystem::getGroup(Group mGroup){
    return groupedentities[mGroup];
}
Entity& EntityComponentSystem::addEntity(){
    Entity* e(new Entity(*this));
    std::unique_ptr<Entity> uPtr(e);
    entities.emplace_back(std::move(uPtr));
    return *e;
}
void EntityComponentSystem::destruct(){
    entities.clear();
    for (auto& group:groupedentities){
        group.clear();
    }
}
void Entity::addGroup(Group mGroup){
    groupbitset[mGroup]=true;
	manager.addToGroup(this,mGroup);
}