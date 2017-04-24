#include <Command.h>
#include <Entity.h>
#include <Utils.h>

Command::Command()
    : entity(NULL),
	  slowThreshold(300), distanceThreshold(25)
{
}

Command::Command(Entity* newEntity, CommandType newCommandType)
    : entity(newEntity), commandType(newCommandType)
{
}

Command::~Command()
{
}

MoveTo::MoveTo(Entity* newEntity, Ogre::Vector3 location)
    : Command(newEntity, Cmd_MoveTo)
{
    targetLocation = location;
    slowThreshold = 150;
    distanceThreshold = 100;
}

MoveTo::~MoveTo()
{

}

void MoveTo::init()
{

}

void MoveTo::tick(float deltaTime)
{
    Ogre::Vector3 target = targetLocation;
    Ogre::Vector3 diff = target - entity->ogreSceneNode->getPosition();
    float heading = -Ogre::Math::ATan2(diff.z, diff.x).valueDegrees();
    //heading = Utils::MakeAnglePosNeg(heading);

    entity->desiredHeading = heading;
    entity->desiredSpeed = entity->maxSpeed;

    if (diff.length() <= slowThreshold)
    {
        entity->desiredSpeed =
        		((diff.length() - distanceThreshold) / (slowThreshold - distanceThreshold)) * entity->maxSpeed;
    }
}

bool MoveTo::done()
{
    Ogre::Vector3 target = targetLocation;
    Ogre::Vector3 diff = target - entity->ogreSceneNode->getPosition();

    if (diff.length() <= distanceThreshold)
    {
        entity->desiredSpeed = 0;
        return true;
    }
    else
    {
        return false;
    }
}

Follow::Follow(Entity* newEntity, Entity* newTarget)
    : Command(newEntity, Cmd_Follow)
{
    targetEntity = newTarget;
    slowThreshold = 300;
    distanceThreshold = 10;

    offset = Ogre::Vector3(-100, 0, 0);
}

Follow::~Follow()
{

}

void Follow::init()
{

}

void Follow::tick(float deltaTime)
{
    Ogre::Vector3 target = targetEntity->ogreSceneNode->getPosition();


    float cos = Ogre::Math::Cos(-targetEntity->heading * Utils::degToRad);
    float sin = Ogre::Math::Sin(-targetEntity->heading * Utils::degToRad);
    Ogre::Vector3 curOffset = Ogre::Vector3(
    		offset.x * cos - offset.z * sin,
			0,
			offset.x * sin + offset.z * cos);
    Ogre::Vector3 diff = target - entity->ogreSceneNode->getPosition() + curOffset;
    float heading = -Ogre::Math::ATan2(diff.z, diff.x).valueDegrees();
    //heading = Utils::MakeAnglePosNeg(heading);

    entity->desiredHeading = heading;
    entity->desiredSpeed = entity->maxSpeed;

    if (diff.length() <= slowThreshold)
    {
    	entity->desiredSpeed =
    			((diff.length() - distanceThreshold) / (slowThreshold - distanceThreshold)) * entity->maxSpeed;
    }
}

bool Follow::done()
{
    Ogre::Vector3 target = targetEntity->ogreSceneNode->getPosition();
    Ogre::Vector3 diff = target - entity->ogreSceneNode->getPosition();

    if (diff.length() <= distanceThreshold)
    {
        entity->desiredSpeed = 0;
        return true;
    }
    else
    {
        return false;
    }
}
