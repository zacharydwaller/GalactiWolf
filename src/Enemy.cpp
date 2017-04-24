#include <Enemy.h>

#include <Utils.h>

Enemy::Enemy(Engine* newEngine)
	: Entity(newEngine)
{
	meshFile = "RZR-002.mesh";

	maxSpeed = 1000;
}

void Enemy::update(float deltaTime)
{
	//lookAt(engine->gameMgr->player->position);

	Entity* player = engine->gameMgr->player;
	Ogre::Vector3 direction = player->position - position;
	direction.normalise();

	if(direction.angleBetween(Ogre::Vector3::NEGATIVE_UNIT_Z).valueDegrees() <= 75)
	{
		velocity = Utils::lerp(velocity, direction * maxSpeed, 0.01);
	}	
}