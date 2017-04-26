#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>

#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include <Engine.h>

class Aspect;
class UnitAI;

class Entity
{
public:
	Entity(Engine* newEngine);
    virtual ~Entity();

    virtual void tick(float deltaTime);

	virtual void awake() = 0;
	virtual void update(float deltaTime) = 0;

	virtual void lookAt(Ogre::Vector3 lookAtPos);

    virtual void moveTo(Ogre::Vector3 location, bool addToCommandList = false);
    virtual void follow(Entity* target, bool addToCommandList = false);

    // Static 
    float maxSpeed, minSpeed;
    float acceleration, turnRate;

    std::string entityName;
    unsigned int entityId;
    std::string meshFile;

	bool isDestroyed;
	bool isEnemy;

    // Dynamic
    float speed, heading;
    float desiredSpeed, desiredHeading;

    bool isSelected;

    // Ogre
    Ogre::Vector3 position;
	Ogre::Vector3 direction;
    Ogre::Vector3 velocity;
    Ogre::SceneNode* ogreSceneNode;
    Ogre::Entity* ogreEntity;

    std::vector<Aspect*>* aspects;
    UnitAI* unitAI;

	Engine* engine;


private:
    static unsigned int nextId;
};

#endif
