#ifndef ISUBSYSTEM_H
#define ISUBSYSTEM_H
// Subsystem interface
class ISubSystem{
    public:
    virtual void init()=0;
    virtual void update()=0;
    virtual void destruct()=0;
    virtual ~ISubSystem()=default;
};
#endif