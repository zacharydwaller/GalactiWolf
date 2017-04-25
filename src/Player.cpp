#include <vector>

#include <Player.h>

#include <Utils.h>

Player::Player(Engine* newEngine)
	: Entity(newEngine)
{
	input = engine->inputMgr;

	fireDelay = 0.1f;
	nextFire = 0.0f;

	meshFile = "razor.mesh";
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
	
	position = Utils::lerp(position, posLocation, 0.01f);
	//player->ogreSceneNode->lookAt(aimLocation, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Y);
	//player->ogreSceneNode->yaw(aimDiff.angleBetween(Ogre::Vector3::UNIT_Z));
	//player->orientation = player->ogreSceneNode->getOrientation();
}

void Player::shoot()
{
	Ogre::Vector3 aimLocation = position + Ogre::Vector3(0, 0, 1000);
	Ogre::Vector3 aimDiff = aimLocation - position;

	// See if player trying to aim at an enemy
	/*
	std::vector<Entity*> entities = input->raycastToEntities();
	if(entities.size() > 0)
	{
		// Player might be in entities list, so skip
		// Entities sorted by distance, so we will aim at closest in raycast
		int i = 0;
		if(entities[0]->entityId != entityId)
		{
			i++;
		}

		// Aim at entity
		if(i < entities.size())
		{
			aimLocation = entities[i]->position;
		}
	}
	*/

	ogreSceneNode->lookAt(aimLocation, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);
}