#include <UnitAI.h>
#include <Entity.h>

UnitAI::UnitAI(Entity* newEntity)
    : Aspect(newEntity)
{
    commandList = new std::list<Command*>();
}

UnitAI::~UnitAI()
{
    commandList->clear();
    delete commandList;
}

void UnitAI::tick(float deltaTime)
{
    if (!commandList->empty())
    {
        Command* curCommand = commandList->front();

        curCommand->tick(deltaTime);

        if (curCommand->done())
        {
            commandList->remove(commandList->front());
        }
    }
}

void UnitAI::setCommand(Command* newCommand)
{
    commandList->clear();
    commandList->push_back(newCommand);
}

void UnitAI::addCommand(Command* newCommand)
{
    commandList->push_back(newCommand);
}