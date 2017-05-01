#include <Laser.h>

#include <vector>

Laser::Laser(Engine* newEngine, float newDamage)
	: Entity(newEngine)
{
	meshFile = "sphere.mesh";

	damage = newDamage;

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

	if(checkCollisions())
	{
		die();
		return;
	}

	lifetime -= deltaTime;

	if(lifetime <= 0)
	{
		die();
		return;
	}
}

bool Laser::checkCollisions()
{
	std::vector<Entity*>* entities = engine->entityMgr->getEntityList();

	for(int i = entities->size() - 1; i >= 0; i--)
	{
		if(isEnemy != entities->at(i)->isEnemy)
		{
			// Hit enemy or player
			if(position.squaredDistance(entities->at(i)->position) <= size*size)
			{
				entities->at(i)->takeDamage(damage);
				
				return true;
			}
		}
	}

	return false;
}

void Laser::setVelocityDirection(Ogre::Vector3 newDirection)
{
	direction = newDirection;
}