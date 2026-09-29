#ifndef ISCENE_H
#define ISCENE_H
// Scene interface
class IScene {
    public:
    virtual void enter()=0;
    virtual void update()=0;
    virtual void print()=0;
    virtual void exit()=0;
    virtual ~IScene()=default;
};

#endif