#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>

class Player : public Entity
{
public:
	Player(Engine* engine);

	void update(float deltaTime);

	void controlShip(float deltaShip);
	void shoot();

	float fireDelay;
	float nextFire;

	InputMgr* input;
};

#endif /* ifndef PLAYER_H */