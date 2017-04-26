#ifndef ENTITY_MGR_H
#define ENTITY_MGR_H

#include <vector>

#include <OgreSceneManager.h>

#include <Mgr.h>
#include <Entity.h>

class EntityMgr : public Mgr
{
public:
    EntityMgr(Engine* newEngine);
    virtual ~EntityMgr();

    void init();
    void stop();

    virtual bool tick(float deltaTime);

    void loadLevel();

    void selectFirstEntity();
    void selectNextEntity();
    void selectEntityAt(int index);
    void selectEntity(Entity* newEntity);

    inline Entity* getSelectedEntity() { return selectedEntity; }
    inline std::vector<Entity*>* getEntityList() { return entities; }

    Entity* getEntityBySceneNode(Ogre::SceneNode* sceneNode);

    Entity* createEntity(Entity* entity, Ogre::Vector3 position = Ogre::Vector3::ZERO, Ogre::Vector3 direction = Ogre::Vector3::UNIT_Z);
	void removeEntity(Entity* entity);

protected:
    int selectedEntityIndex;
    Entity* selectedEntity;
    std::vector<Entity*>* entities;

    Ogre::SceneManager* sceneMgr;
};

#endif