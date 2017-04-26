#ifndef INPUT_MGR_H
#define INPUT_MGR_H

#include <OgreRenderWindow.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>

#include <OgreVector3.h>
#include <OgreQuaternion.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <Mgr.h>

class Entity;

class InputMgr : public Mgr, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
    InputMgr(Engine* newEngine);
    virtual ~InputMgr();

    void init();
    void stop();

    virtual bool tick(float deltaTime);

    void loadLevel();

	std::vector<Entity*> raycastToEntities();
	Ogre::Vector3 raycastToPlane(Ogre::Plane plane, float offset = 0);

	OIS::Mouse* mouse;
	OIS::Keyboard* keyboard;

protected:
    void controlCamera(float deltaTime);
    void moveCamera(Ogre::Vector3 movement);
    void rotateCamera(float yaw, float pitch);

    void initializeOIS();

    bool keyPressed(const OIS::KeyEvent &arg);
    bool keyReleased(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    void windowResized(Ogre::RenderWindow* rw);
    void windowClosed(Ogre::RenderWindow* rw);

    Ogre::Camera* camera;
    Ogre::RenderWindow* window;

    OIS::InputManager* inputManager;
};

#endif