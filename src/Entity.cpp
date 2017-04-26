#include <Engine.h>

#include <Utils.h>

#include <Entity.h>
#include <Aspect.h>
#include <UnitAI.h>

unsigned int Entity::nextId = 0;

Entity::Entity(Engine* newEngine)
{
	engine = newEngine;
	isDestroyed = false;

	// Set position/speed
	position = Ogre::Vector3::ZERO;
	heading = 0;
	velocity = Ogre::Vector3::ZERO;
	speed = 0;

	desiredHeading = heading;
	desiredSpeed = 0;

	isSelected = false;

	entityId = Entity::nextId++;

	// Initialize aspects
	aspects = new std::vector<Aspect*>();
	aspects->push_back(new Physics(this));
	aspects->push_back(new Renderer(this));

	//unitAI = new UnitAI(this);
	//aspects->push_back(unitAI);
}

Entity::~Entity()
{
    aspects->clear();
    delete aspects;
	aspects = NULL;
}

void Entity::tick(float deltaTime)
{
	update(deltaTime);

	if(isDestroyed) return;
    for (int i = aspects->size() - 1; i >= 0; i--)
    {
        aspects->at(i)->tick(deltaTime);
    }
}

void Entity::lookAt(Ogre::Vector3 lookAtPos)
{
	// TODO: Fix this
	Ogre::Vector3 forward;

	forward = lookAtPos - position;
	forward.normalise();

	direction = forward;
}

void Entity::moveTo(Ogre::Vector3 location, bool addToCommandList)
{
    MoveTo* command = new MoveTo(this, location);
    
    if (addToCommandList)
    {
        unitAI->addCommand(command);
    }
    else
    {
        unitAI->setCommand(command);
    }

    command->init();
}

void Entity::follow(Entity* target, bool addToCommandList)
{
    Follow* command = new Follow(this, target);

    if (addToCommandList)
    {
        unitAI->addCommand(command);
    }
    else
    {
        unitAI->setCommand(command);
    }

    command->init();
}
