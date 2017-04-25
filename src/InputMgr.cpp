#include <InputMgr.h>
#include <Entity.h>
#include <Engine.h>

#include <Utils.h>

InputMgr::InputMgr(Engine* newEngine)
    : Mgr(newEngine),
    window(0),
    inputManager(0), mouse(0), keyboard(0)
{

}

InputMgr::~InputMgr()
{
}

void InputMgr::init()
{
    window = engine->gfxMgr->getWindow();
    camera = engine->gfxMgr->getCamera();

    initializeOIS();
}

void InputMgr::stop()
{
    Ogre::WindowEventUtilities::removeWindowEventListener(window, this);
    windowClosed(window);
}

bool InputMgr::tick(float deltaTime)
{
    static bool tabDownLastFrame = false;
    static bool lmbDownLastFrame = false;
    static bool rmbDownLastFrame = false;

    keyboard->capture();
    mouse->capture();

    if (keyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        engine->keepRunning = false;
        return false;
    }

	/*
    if (keyboard->isKeyDown(OIS::KC_TAB) && !tabDownLastFrame)
    {
        engine->entityMgr->selectNextEntity();
        tabDownLastFrame = true;
    }
    if (!keyboard->isKeyDown(OIS::KC_TAB))
        tabDownLastFrame = false;

    if (mouse->getMouseState().buttonDown(OIS::MB_Left) && !lmbDownLastFrame)
    {
        processLeftClick();
        lmbDownLastFrame = true;
    }
    if (!mouse->getMouseState().buttonDown(OIS::MB_Left))
    {
        lmbDownLastFrame = false;
    }

    if (mouse->getMouseState().buttonDown(OIS::MB_Right) && !rmbDownLastFrame)
    {
        processRightClick();
        rmbDownLastFrame = true;
    }
    if (mouse->getMouseState().buttonDown(OIS::MB_Right))
    {
        rmbDownLastFrame = false;
    }
    
	*/

	controlCamera(deltaTime);

    return true;
}

void InputMgr::loadLevel()
{

}

void InputMgr::controlCamera(float deltaTime)
{
    Ogre::Vector3 cameraMovement = Ogre::Vector3::ZERO;

    Ogre::Quaternion camDir = camera->getOrientation();
    float cameraYaw = 0;
    float cameraPitch = 0;
    float cameraSpeed = 500 * deltaTime;
    float cameraRotSpeed = Ogre::Math::HALF_PI * deltaTime;
    float groundHeight = 25;

    if (keyboard->isKeyDown(OIS::KC_LSHIFT))
    {
        cameraSpeed *= 2;
        cameraRotSpeed *= 2;
    }

    // Forward / Backward
    if (keyboard->isKeyDown(OIS::KC_W))
        cameraMovement += -camDir.zAxis() * cameraSpeed;
    if (keyboard->isKeyDown(OIS::KC_S))
        cameraMovement += camDir.zAxis() * cameraSpeed;
    cameraMovement.y = 0;

    // Left / Right
    if (keyboard->isKeyDown(OIS::KC_A))
        cameraMovement += -camDir.xAxis() * cameraSpeed;
    if (keyboard->isKeyDown(OIS::KC_D))
        cameraMovement += camDir.xAxis() * cameraSpeed;

    // Up / Down
    if (keyboard->isKeyDown(OIS::KC_R))
        cameraMovement.y += cameraSpeed;
    if (keyboard->isKeyDown(OIS::KC_F) && camera->getPosition().y > groundHeight)
        cameraMovement.y += -cameraSpeed;

    // Yaw
    if (keyboard->isKeyDown(OIS::KC_Q))
        cameraYaw += cameraRotSpeed;
    if (keyboard->isKeyDown(OIS::KC_E))
        cameraYaw += -cameraRotSpeed;

    // Pitch
    if (keyboard->isKeyDown(OIS::KC_Z))
        cameraPitch += -cameraRotSpeed;
    if (keyboard->isKeyDown(OIS::KC_X))
        cameraPitch += cameraRotSpeed;


    moveCamera(cameraMovement);
    rotateCamera(cameraYaw, cameraPitch);
}

void InputMgr::moveCamera(Ogre::Vector3 movement)
{
    camera->setPosition(camera->getPosition() + movement);
}

void InputMgr::rotateCamera(float yaw, float pitch)
{
    camera->yaw(Ogre::Radian(yaw));
    camera->pitch(Ogre::Radian(pitch));
}


std::vector<Entity*> InputMgr::raycastToEntities()
{
    std::vector<Entity*> ret;

    Ogre::Real screenWidth  = engine->gfxMgr->getWindow()->getWidth();
    Ogre::Real screenHeight = engine->gfxMgr->getWindow()->getHeight();
    OIS::MouseState mouseState = mouse->getMouseState();
    
    Ogre::Real offsetX = mouseState.X.abs / screenWidth;
    Ogre::Real offsetY = mouseState.Y.abs / screenHeight;

    Ogre::Ray mouseRay = camera->getCameraToViewportRay(offsetX, offsetY);
    Ogre::RaySceneQuery* rayQuery = engine->gameMgr->sceneMgr->createRayQuery(mouseRay);

    rayQuery->setRay(mouseRay);
    rayQuery->setSortByDistance(true);

    Ogre::RaySceneQueryResult& rayResult = rayQuery->execute();
    Ogre::RaySceneQueryResult::iterator it = rayResult.begin();

    for (; it != rayResult.end(); it++)
    {
        if (it->movable
            && it->movable->getName() != ""
            && it->movable->getName() != camera->getName())
        {
            ret.push_back(engine->entityMgr->getEntityBySceneNode(it->movable->getParentSceneNode()));
        }
    }

    return ret;
}

Ogre::Vector3 InputMgr::raycastToPlane(Ogre::Plane plane)
{
    Ogre::Real screenWidth = engine->gfxMgr->getWindow()->getWidth();
    Ogre::Real screenHeight = engine->gfxMgr->getWindow()->getHeight();
    OIS::MouseState mouseState = mouse->getMouseState();

    Ogre::Real offsetX = mouseState.X.abs / screenWidth;
    Ogre::Real offsetY = mouseState.Y.abs / screenHeight;

    Ogre::Ray mouseRay = camera->getCameraToViewportRay(offsetX, offsetY);

    std::pair<bool, float> result = mouseRay.intersects(plane);

    if (result.first)
    {
        return mouseRay.getPoint(result.second);
    }
}

void InputMgr::initializeOIS()
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    window->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

#if defined OIS_WIN32_PLATFORM
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
    pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

    inputManager = OIS::InputManager::createInputSystem(pl);

    keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
    mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));

    mouse->setEventCallback(this);
    keyboard->setEventCallback(this);

    // Set initial mouse clipping size
    windowResized(window);

    // Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(window, this);
}

bool InputMgr::keyPressed(const OIS::KeyEvent& arg)
{
    return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& arg)
{
    return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& arg)
{
    return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    return true;
}

void InputMgr::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void InputMgr::windowClosed(Ogre::RenderWindow* rw)
{
    if (rw == window)
    {
        if (inputManager)
        {
            inputManager->destroyInputObject(mouse);
            inputManager->destroyInputObject(keyboard);

            OIS::InputManager::destroyInputSystem(inputManager);
            inputManager = 0;
        }
    }
}
