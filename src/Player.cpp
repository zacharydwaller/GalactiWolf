#include <vector>

#include <Player.h>
#include <Laser.h>

#include <Utils.h>

Player::Player(Engine* newEngine)
	: Entity(newEngine)
{
	input = engine->inputMgr;

	health = 100;
	damage = 35;

	speed = 1500;

	extraLives = 2;

	fireDelay = 0.2f;
	nextFire = 0.0f;

	meshFile = "razor.mesh";

	isEnemy = false;
}

void Player::awake()
{

}

void Player::update(float deltaTime)
{
	controlShip(deltaTime);

	if(input->mouse->getMouseState().buttonDown(OIS::MB_Left)
		&& engine->time >= nextFire)
	{
		nextFire = engine->time + fireDelay;
		shoot();
	}
}

void Player::controlShip(float deltaTime)
{
	Ogre::Vector3 posLocation = input->raycastToPlane(engine->gameMgr->positionPlane);
	Ogre::Vector3 aimLocation = input->raycastToPlane(engine->gameMgr->aimPlane, 5000);

	lookAt(aimLocation);
	
	position = Utils::lerp(position, posLocation, (speed / 1000.0f) * deltaTime);
	//position = Utils::lerp(position, posLocation, 0.025f);
	//position = Utils::SmoothDamp(position, posLocation, speed * deltaTime);
}

void Player::shoot()
{
	Laser* laser = (Laser*) engine->entityMgr->createEntity(new Laser(engine, damage), position, direction);
	laser->isEnemy = false;
}

void Player::die()
{
	if(extraLives == 0)
	{
		// Game over
		engine->entityMgr->removeEntity(this);
		isDestroyed = true;
	}
	else
	{
		extraLives--;
		health = 100;
	}
}