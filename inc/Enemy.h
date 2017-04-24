#ifndef ENEMY_H
#define ENEMY_H

#include <Entity.h>

class Enemy : public Entity
{
public:
	Enemy(Engine* newEngine);

	void update(float deltaTime);
};

#endif /* ifndef ENEMY_H */