#ifndef ENEMY_H
#define ENEMY_H

#include <Entity.h>

class Enemy : public Entity
{
public:
	Enemy(Engine* newEngine);

	void awake();
	void update(float deltaTime);

	// Returns true if hit something
	bool checkCollisions();

	float damage;

	float acceleration;
	float rotationSpeed;

	float maxSpeed;

	float size;
	float lifetime;
};

#endif /* ifndef ENEMY_H */