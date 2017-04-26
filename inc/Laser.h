#ifndef LASER_H
#define LASER_H

#include <OgreVector3.h>

#include <Entity.h>

class Laser : public Entity
{
public:
	Laser(Engine* newEngine);

	void awake();
	void update(float deltaTime);

	void checkCollisions();

	void setVelocityDirection(Ogre::Vector3 newDirection);

	float size;
	float speed;
	float lifetime;
};

#endif /* ifndef LASER_H */