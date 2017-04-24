#include <GfxMgr.h>
#include <Engine.h>

GfxMgr::GfxMgr(Engine* newEngine)
	: Mgr(newEngine),
	root(0),
	camera(0),
	sceneMgr(0),
	window(0),
	resourcesCfg(Ogre::StringUtil::BLANK),
	pluginsCfg(Ogre::StringUtil::BLANK)
{
}

GfxMgr::~GfxMgr()
{
	delete root;
}

void GfxMgr::init()
{
#ifdef _DEBUG
#ifndef OGRE_STATIC_LIB
	resourcesCfg = "resources_d.cfg";
	pluginsCfg = "plugins_d.cfg";
#else
	resourcesCfg = "resources_d.cfg";
	pluginsCfg = "plugins_d.cfg";
#endif
#else
#ifndef OGRE_STATIC_LIB
	resourcesCfg = "resources.cfg";
	pluginsCfg = "plugins.cfg";
#else
	resourcesCfg = "resources.cfg";
	pluginsCfg = "plugins.cfg";
#endif
#endif

	setup();
}

void GfxMgr::stop()
{

}

bool GfxMgr::tick(float deltaTime)
{
	Ogre::WindowEventUtilities::messagePump();

	if(window->isClosed())
	{
		engine->keepRunning = false;
		return false;
	}
	if(!root->renderOneFrame())
	{
		engine->keepRunning = false;
		return false;
	}

	return true;
}

void GfxMgr::loadLevel()
{

}

bool GfxMgr::setup()
{
	root = new Ogre::Root(pluginsCfg);

	setupResources();
	configure();

	createSceneManager();
	createCamera();
	createViewports();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	createResourceListener();
	loadResources();

	return true;
}


void GfxMgr::setupResources()
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(resourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while(seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for(i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
}

bool GfxMgr::configure()
{
	if(root->showConfigDialog())
	{
		window = root->initialise(true, "GalactiWolf");
		return true;
	}
	else
	{
		return false;
	}
}

void GfxMgr::createSceneManager()
{
	sceneMgr = root->createSceneManager(Ogre::ST_GENERIC);
}

void GfxMgr::createCamera()
{
	camera = sceneMgr->createCamera("PlayerCam");

	camera->setPosition(Ogre::Vector3(0, 0, -500));
	camera->lookAt(Ogre::Vector3(0, 0, 0));

	camera->setNearClipDistance(5);
}

void GfxMgr::createViewports()
{
	Ogre::Viewport* vp = window->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue::Black);

	camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}


void GfxMgr::createResourceListener()
{
}

void GfxMgr::loadResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
