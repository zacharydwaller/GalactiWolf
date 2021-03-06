#ifndef ENGINE_H
#define ENGINE_H

#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <UiMgr.h>

class GameMgr;
class InputMgr;
class EntityMgr;
class GfxMgr;

class Engine
{
public:
    Engine();
    ~Engine();

    void init();

    void run();
    void stop();
    void shutdown();

    bool tickAll(float deltaTime);

	float time;

	UiMgr*		uiMgr;
    GameMgr*    gameMgr;
    InputMgr*   inputMgr;
    EntityMgr*  entityMgr;
    GfxMgr*     gfxMgr;

    bool keepRunning;
};


#endif