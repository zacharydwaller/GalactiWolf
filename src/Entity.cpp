#include <Engine.h>

#include <Entity.h>
#include <Aspect.h>
#include <UnitAI.h>

unsigned int Entity::nextId = 0;

Entity::Entity()
{
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
	aspects = new std::list<Aspect*>();
	aspects->push_back(new Physics(this));
	aspects->push_back(new Renderer(this));

	//unitAI = new UnitAI(this);
	//aspects->push_back(unitAI);
}

Entity::~Entity()
{
    aspects->clear();
    delete aspects;
}

void Entity::tick(float deltaTime)
{
    std::list<Aspect*>::iterator it;
    for (it = aspects->begin(); it != aspects->end(); it++)
    {
        (*it)->tick(deltaTime);
    }
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
