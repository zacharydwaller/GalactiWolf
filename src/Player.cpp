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
	Ogre::Vector3 aimLocation = input->raycastToPlane(engine->gameMgr->aimPlane);
	Ogre::Vector3 aimDiff = aimLocation - position;

	position = Utils::lerp(position, posLocation, 0.01f);

	//ogreSceneNode->lookAt(aimLocation, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);
	ogreSceneNode->setDirection(aimDiff, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);

	//player->ogreSceneNode->lookAt(aimLocation, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Y);
	//player->ogreSceneNode->yaw(aimDiff.angleBetween(Ogre::Vector3::UNIT_Z));
	//player->orientation = player->ogreSceneNode->getOrientation();
}

void Player::shoot()
{
}