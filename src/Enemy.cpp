#include <Enemy.h>

#include <Utils.h>

Enemy::Enemy(Engine* newEngine)
	: Entity(newEngine)
{
	meshFile = "RZR-002.mesh";

	maxSpeed = 1000;

	size = 100;
	lifetime = 10;

	isEnemy = true;
}

void Enemy::awake()
{
	ogreSceneNode->scale(5, 5, 5);
}

void Enemy::update(float deltaTime)
{
	Entity* player = engine->gameMgr->player;
	if(player != NULL)
	{
		lookAt(player->position);
		checkCollisions();
	}

	if(direction.angleBetween(Ogre::Vector3::NEGATIVE_UNIT_Z).valueDegrees() <= 75)
	{
		velocity = Utils::lerp(velocity, direction * maxSpeed, 0.01);
	}

	direction = velocity.normalisedCopy();

	lifetime -= deltaTime;
	if(lifetime <= 0)
	{
		engine->entityMgr->removeEntity(this);
	}
}

void Enemy::checkCollisions()
{
	std::vector<Entity*>* entities = engine->entityMgr->getEntityList();

	for(int i = entities->size() - 1; i >= 0; i--)
	{
		if(entities->at(i)->isEnemy == false)
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