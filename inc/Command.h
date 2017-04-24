#ifndef COMMAND_H
#define COMMAND_H

#include <OgreVector3.h>

class Entity;

enum CommandType
{
    Cmd_MoveTo, Cmd_Follow
};

class Command
{
public:
    Command();
    Command(Entity* newEntity, CommandType newCommandType);
    virtual ~Command();

    virtual void init() = 0;
    virtual void tick(float deltaTime) = 0;
    virtual bool done() = 0;

    Entity* entity;
    CommandType commandType;

    float slowThreshold;
    float distanceThreshold;
};

class MoveTo : public Command
{
public:
    MoveTo(Entity* newEntity, Ogre::Vector3 location);
    ~MoveTo();

    void init();
    void tick(float deltaTime);
    bool done();

    Ogre::Vector3 targetLocation;
};

class Follow : public Command
{
public:
    Follow(Entity* newEntity, Entity* newTarget);
    ~Follow();

    void init();
    void tick(float deltaTime);
    bool done();

    Entity* targetEntity;
    Ogre::Vector3 offset;
};

#endif /* #ifndef COMMAND_H */
