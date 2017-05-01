#include <UiMgr.h>
#include <Engine.h>

UiMgr::UiMgr(Engine* newEngine)
	: Mgr(newEngine)
{
	// This line causes some Ogre assertion to fail
	overlaySystem = new Ogre::OverlaySystem();
	engine->gfxMgr->getSceneMgr()->addRenderQueueListener(overlaySystem);
}

UiMgr::~UiMgr()
{

}

void UiMgr::init()
{
	inputContext.mKeyboard = engine->inputMgr->keyboard;
	inputContext.mMouse = engine->inputMgr->mouse;
	trayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->getWindow(), inputContext, this);
	trayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	trayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
	//mTrayMgr->hideCursor();
}

void UiMgr::stop()
{

}

void UiMgr::loadLevel()
{
	trayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Click Me!");
	trayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Menu", 100, 20, 10);
}

bool UiMgr::tick(float deltaTime)
{
	trayMgr->refreshCursor();
	return true;
}

void UiMgr::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw)
{

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg)
{
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}

bool UiMgr::keyReleased(const OIS::KeyEvent &arg)
{
	return true;
}

bool UiMgr::mouseMoved(const OIS::MouseEvent &arg)
{
	if(trayMgr->injectMouseMove(arg)) return true;
	/* normal mouse processing here... */
	return true;
}

bool UiMgr::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	std::cout << "mouse clicked" << std::endl;
	if(trayMgr->injectMouseDown(arg, id)) return true;
	/* normal mouse processing here... */
	return true;
}

bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if(trayMgr->injectMouseUp(arg, id)) return true;
	/* normal mouse processing here... */
	return true;
}

void UiMgr::buttonHit(OgreBites::Button *b)
{
	if(b->getName() == "MyButton")
	{
		std::cout << "Click Me!" << std::endl;
	}

}

void UiMgr::itemSelected(OgreBites::SelectMenu *m)
{
	if(m->getName() == "MyMenu")
	{
		std::cout << "Menu!" << std::endl;
	}

}
