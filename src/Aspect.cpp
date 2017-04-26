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

    updatePosition();
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
	entity->ogreSceneNode->setDirection(entity->direction, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);

    if (entity->isSelected)
        entity->ogreSceneNode->showBoundingBox(true);
    else
        entity->ogreSceneNode->showBoundingBox(false);
}
