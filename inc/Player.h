#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>

class Player : public Entity
{
public:
	Player(Engine* engine);

	void awake();
	void update(float deltaTime);

	void controlShip(float deltaShip);
	void shoot();

	void die();

	float damage;

	float speed;

	int extraLives;

	float fireDelay;
	float nextFire;

	InputMgr* input;
};

#endif /* ifndef PLAYER_H */