#ifndef UNITAI_H
#define UNITAI_H

#include <Aspect.h>
#include <Command.h>
#include <list>

class UnitAI : public Aspect
{
public:
    UnitAI(Entity* newEntity);
    ~UnitAI();

    void tick(float deltaTime);
    void setCommand(Command* newCommand);
    void addCommand(Command* newCommand);

    std::list<Command*>* commandList;
};

#endif /* #ifndef UNITAI_H */