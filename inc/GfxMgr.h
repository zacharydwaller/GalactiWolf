#ifndef GFX_MGR_H
#define GFX_MGR_H

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreConfigFile.h>

#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// D3D10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif
#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  include "OgreStaticPluginLoader.h"
#endif

#include <Mgr.h>

class GfxMgr : public Mgr
{
public:
	GfxMgr(Engine* newEngine);
	virtual ~GfxMgr();

	void init();
	void stop();

	virtual bool tick(float deltaTime);

	void loadLevel();

	inline Ogre::Root* getRoot() { return root; }
	inline Ogre::Camera* getCamera() { return camera; }
	inline Ogre::SceneManager* getSceneMgr() { return sceneMgr; }
	inline Ogre::RenderWindow* getWindow() { return window; }


protected:

	virtual bool setup();

	virtual void setupResources();
	virtual bool configure();

	virtual void createSceneManager();
	virtual void createCamera();
	virtual void createViewports();

	virtual void createResourceListener();
	virtual void loadResources();

	Ogre::Root*                 root;
	Ogre::Camera*               camera;
	Ogre::SceneManager*         sceneMgr;
	Ogre::RenderWindow*         window;
	Ogre::String                resourcesCfg;
	Ogre::String                pluginsCfg;
};

#endif