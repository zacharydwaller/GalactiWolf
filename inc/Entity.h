#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <list>

#include <OgreEntity.h>
#include <OgreSceneNode.h>

class Aspect;
class UnitAI;

class Entity
{
public:
	Entity();
    virtual ~Entity();

    virtual void tick(float deltaTime);

    virtual void moveTo(Ogre::Vector3 location, bool addToCommandList = false);
    virtual void follow(Entity* target, bool addToCommandList = false);

    // Static 
    float maxSpeed, minSpeed;
    float acceleration, turnRate;

    std::string entityName;
    unsigned int entityId;
    std::string meshFile;

    // Dynamic
    float speed, heading;
    float desiredSpeed, desiredHeading;

    bool isSelected;

    // Ogre
    Ogre::Vector3 position;
    Ogre::Vector3 velocity;
    Ogre::SceneNode* ogreSceneNode;
    Ogre::Entity* ogreEntity;

    std::list<Aspect*>* aspects;
    UnitAI* unitAI;

private:
    static unsigned int nextId;
};

#endif
