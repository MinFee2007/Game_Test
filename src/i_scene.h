#ifndef ISCENE_H
#define ISCENE_H
// Scene interface
class IScene {
    public:
    virtual void onEnter()=0;
    virtual void onUpdate()=0;
    virtual void onExit()=0;
    virtual ~IScene()=default;
};

#endif