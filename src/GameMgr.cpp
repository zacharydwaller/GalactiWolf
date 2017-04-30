#include <GameMgr.h>
#include <Engine.h>

#include <Player.h>
#include <Enemy.h>

#include <stdlib.h>
#include <time.h>

GameMgr::GameMgr(Engine* newEngine)
    : Mgr(newEngine)
{
	srand(time(NULL));

	enemySpawnDelay = 1.0f;
	nextEnemySpawn = 1.0f;
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
	enemySpawnDelay -= 0.01f * deltaTime;
	if(enemySpawnDelay <= 0.25) enemySpawnDelay = 0.25;

	if(player != NULL)
	{
		if(engine->time >= nextEnemySpawn)
		{
			nextEnemySpawn = engine->time + enemySpawnDelay;

			Ogre::Vector3 pos(-2500 + (rand() % 5000), -100 + (rand() % 2000), 5000);

			engine->entityMgr->createEntity(new Enemy(engine), pos);
		}
	}
	
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
	// Create player entity
    EntityMgr* entityMgr = engine->entityMgr;
	player = entityMgr->createEntity(new Player(engine));

	// Create position plane
	positionPlane = Ogre::Plane(Ogre::Vector3::NEGATIVE_UNIT_Z, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"PositionPlane",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		positionPlane,
		10000, 10000);
	Ogre::Entity* posPlaneEnt = sceneMgr->createEntity("PositionPlane");
	Ogre::SceneNode* posPlaneSceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	posPlaneSceneNode->attachObject(posPlaneEnt);
	posPlaneEnt->setMaterialName("Examples/GrassFloor");
	posPlaneSceneNode->setPosition(0, 0, 0);
	posPlaneEnt->setVisible(false);

	// Create aim plane
	aimPlane = Ogre::Plane(Ogre::Vector3::NEGATIVE_UNIT_Z, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"AimPlane",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		aimPlane,
		10000, 10000);
	Ogre::Entity* aimPlaneEnt = sceneMgr->createEntity("AimPlane");
	Ogre::SceneNode* aimPlaneSceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
	aimPlaneSceneNode->attachObject(aimPlaneEnt);
	aimPlaneEnt->setMaterialName("Examples/GrassFloor");
	aimPlaneSceneNode->setPosition(0, 0, 5000);
	aimPlaneEnt->setVisible(false);
}
