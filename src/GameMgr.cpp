#include <GameMgr.h>
#include <Engine.h>

#include <Player.h>

GameMgr::GameMgr(Engine* newEngine)
    : Mgr(newEngine)
{

}

GameMgr::~GameMgr()
{

}

void GameMgr::init()
{
    sceneMgr = engine->gfxMgr->getSceneMgr();
}

void GameMgr::stop()
{

}

bool GameMgr::tick(float deltaTime)
{
    return true;
}

void GameMgr::loadLevel()
{
    createScene();
}

void GameMgr::createScene()
{
    createLighting();
    createSky();
    createPlayer();
}

void GameMgr::createLighting()
{
    sceneMgr->setAmbientLight(Ogre::ColourValue(.50, .50, .50));
    sceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    Ogre::Light* directionalLight = sceneMgr->createLight("DirectionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(1.0, 0.8, 0.5));
    directionalLight->setSpecularColour(Ogre::ColourValue(0.5, 0.3, 0.2));
    directionalLight->setDirection(Ogre::Vector3(0.55, -0.3, 0.75));
}

void GameMgr::createSky()
{
    //mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
    sceneMgr->setSkyBox(true, "Examples/MorningSkyBox");
}

void GameMgr::createPlayer()
{
    EntityMgr* entityMgr = engine->entityMgr;
	player = entityMgr->createEntity(new Player());
}
