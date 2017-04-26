#include <Laser.h>

#include <vector>

Laser::Laser(Engine* newEngine)
	: Entity(newEngine)
{
	meshFile = "sphere.mesh";

	size = 100;
	speed = 4000.0f;
	lifetime = 2.0f;
}

void Laser::awake()
{
	ogreSceneNode->setScale(0.1f, 0.1f, 0.1f);
}

void Laser::update(float deltaTime)
{
	velocity = direction * speed;

	checkCollisions();

	lifetime -= deltaTime;

	if(lifetime <= 0)
	{
		engine->entityMgr->removeEntity(this);
	}
}

void Laser::checkCollisions()
{
	std::vector<Entity*>* entities = engine->entityMgr->getEntityList();

	for(int i = entities->size() - 1; i >= 0; i--)
	{
		if(isEnemy != entities->at(i)->isEnemy)
		{
			if(position.squaredDistance(entities->at(i)->position) <= size*size)
			{
				engine->entityMgr->removeEntity(entities->at(i));
				lifetime = 0;
				return;
			}
		}
	}
}

void Laser::setVelocityDirection(Ogre::Vector3 newDirection)
{
	direction = newDirection;
}