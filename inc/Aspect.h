#ifndef ASPECT_H
#define ASPECT_H

class Entity;

class Aspect
{
public:
    Aspect();
    Aspect(Entity* newEntity);
    virtual ~Aspect();

    virtual void tick(float deltaTime) = 0;

    Entity* entity;
};

class Physics : public Aspect
{
public:
    Physics(Entity* newEntity);

    virtual void tick(float newDeltaTime);

private:
    virtual void updateSpeed();
    virtual void updateHeading();
    virtual void updateVelocity();
    virtual void updatePosition();

    float deltaTime;
};

class Renderer : public Aspect
{
public:
    Renderer(Entity* newEntity);

    virtual void tick(float deltaTime);
};

#endif
