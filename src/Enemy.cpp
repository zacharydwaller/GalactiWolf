#include <Enemy.h>

#include <Utils.h>

Enemy::Enemy(Engine* newEngine)
	: Entity(newEngine)
{
	meshFile = "RZR-002.mesh";

	health = 100;
	damage = 25;

	acceleration = 500;
	rotationSpeed = 10;

	maxSpeed = 1000;

	size = 100;
	lifetime = 10;

	isEnemy = true;
}

void Enemy::awake()
{
	ogreSceneNode->scale(5, 5, 5);

	Entity* player = engine->gameMgr->player;
	if(player != NULL)
	{
		lookAt(player->position);
	}
}

void Enemy::update(float deltaTime)
{
	Entity* player = engine->gameMgr->player;

	if(player != NULL)
	{
		if(checkCollisions())
		{
			die();
			return;
		}

		if(direction.angleBetween(Ogre::Vector3::NEGATIVE_UNIT_Z).valueDegrees() <= 75)
		{
			lookAt(player->position);
			velocity = Utils::MoveTo(velocity, direction * maxSpeed, acceleration * deltaTime);
		}
	}

	direction = velocity.normalisedCopy();

	lifetime -= deltaTime;
	if(lifetime <= 0)
	{
		die();
		return;
	}

}

bool Enemy::checkCollisions()
{
	std::vector<Entity*>* entities = engine->entityMgr->getEntityList();

	for(int i = entities->size() - 1; i >= 0; i--)
	{
		// If hit player
		if(entities->at(i)->isEnemy == false)
		{
			if(position.squaredDistance(entities->at(i)->position) <= size*size)
			{
				entities->at(i)->takeDamage(damage);
				return true;
			}
		}
	}

	return false;
}