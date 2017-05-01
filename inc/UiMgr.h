#ifndef INC_UIMGR_H_
#define INC_UIMGR_H_

#include <OgreWindowEventUtilities.h>
#include <SdkTrays.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <Mgr.h>

class UiMgr : public Mgr, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener, public OgreBites::SdkTrayListener
{
public:

	UiMgr(Engine *newEngine);
	virtual ~UiMgr();

	virtual void init();
	virtual void stop();
	virtual bool tick(float deltaTime);

	virtual void loadLevel();

	OgreBites::InputContext inputContext;
	OgreBites::SdkTrayManager* trayMgr;
	Ogre::OverlaySystem* overlaySystem;

protected:
	virtual void windowResized(Ogre::RenderWindow *rw);
	virtual void windowClosed(Ogre::RenderWindow *rw);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void buttonHit(OgreBites::Button *b);
	void itemSelected(OgreBites::SelectMenu *m);
};

#endif /* INC_UIMGR_H_ */
