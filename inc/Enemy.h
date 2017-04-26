#ifndef ENEMY_H
#define ENEMY_H

#include <Entity.h>

class Enemy : public Entity
{
public:
	Enemy(Engine* newEngine);

	void awake();
	void update(float deltaTime);

	void checkCollisions();

	float size;
	float lifetime;
};

#endif /* ifndef ENEMY_H */