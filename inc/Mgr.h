#ifndef MGR_H
#define MGR_H

class Engine;

class Mgr
{
public:
    Mgr(Engine* newEngine);
    virtual ~Mgr();

    virtual void init() = 0;
    virtual void stop() = 0;

    virtual bool tick(float deltaTime) = 0;

    virtual void loadLevel() = 0;

    Engine* engine;
};

#endif