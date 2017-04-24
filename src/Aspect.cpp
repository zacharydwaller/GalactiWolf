#include <Aspect.h>
#include <Entity.h>
#include <Utils.h>

Aspect::Aspect()
    : entity(NULL)
{
}

Aspect::Aspect(Entity* newEntity)
    : entity(newEntity)
{
}

Aspect::~Aspect()
{
    entity = NULL;
}

Physics::Physics(Entity* newEntity)
    : Aspect(newEntity)
{
}

void Physics::tick(float newDeltaTime)
{
    deltaTime = newDeltaTime;

    updateSpeed();
    //updateHeading();
    updateVelocity();
    updatePosition();
}

void Physics::updateSpeed()
{
    if (entity->speed < entity->desiredSpeed)
    {
        entity->speed += entity->acceleration * deltaTime;
    }
    else if (entity->speed > entity->desiredSpeed)
    {
        entity->speed -= entity->acceleration * deltaTime;
    }
    Ogre::Math::Clamp(entity->speed, entity->minSpeed, entity->maxSpeed);
}

void Physics::updateHeading()
{
    float diff =
        Utils::DifferenceBetweenAngles(entity->heading, entity->desiredHeading);
    float curTurnSpeed = entity->turnRate * deltaTime;

    if(Ogre::Math::Abs(diff) >= curTurnSpeed)
    {
    	if (diff < 0)
		{
			entity->heading += curTurnSpeed;
		}
		else if (diff > 0)
		{
			entity->heading -= curTurnSpeed;
		}
    }
}

void Physics::updateVelocity()
{
    entity->velocity = entity->ogreSceneNode->getOrientation().xAxis() * entity->speed;
}

void Physics::updatePosition()
{
    entity->position += entity->velocity * deltaTime;
}

Renderer::Renderer(Entity* newEntity)
    : Aspect(newEntity)
{
}

void Renderer::tick(float deltaTime)
{
    entity->ogreSceneNode->setPosition(entity->position);
    entity->ogreSceneNode->setOrientation(entity->orientation);

    if (entity->isSelected)
        entity->ogreSceneNode->showBoundingBox(true);
    else
        entity->ogreSceneNode->showBoundingBox(false);
}
