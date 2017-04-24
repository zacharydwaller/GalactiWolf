#ifndef GAME_MGR_H
#define GAME_MGR_H

#include <OgreSceneManager.h>
#include <OgreMeshManager.h>

#include <Mgr.h>

class Entity;

class GameMgr : public Mgr
{
public:
    GameMgr(Engine* newEngine);
    virtual ~GameMgr();

    void init();
    void stop();

    virtual bool tick(float deltaTime);

    void loadLevel();

	Entity* player;

//protected:
    void createScene();
    void createLighting();
    void createSky();
    void createPlayer();

    Ogre::SceneManager* sceneMgr;

    Ogre::Plane groundPlane;
};

#endif