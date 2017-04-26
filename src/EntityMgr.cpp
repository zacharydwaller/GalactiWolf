#include "EntityMgr.h"
#include "Engine.h"

EntityMgr::EntityMgr(Engine* newEngine)
    : Mgr(newEngine)
{
    selectedEntityIndex = 0;
    selectedEntity = NULL;
    entities = new std::vector<Entity*>();
}

EntityMgr::~EntityMgr()
{
    delete entities;
}

void EntityMgr::init()
{
    sceneMgr = engine->gfxMgr->getSceneMgr();
}

void EntityMgr::stop()
{
    entities->clear();
}

bool EntityMgr::tick(float deltaTime)
{
    std::vector<Entity*>::iterator it;
	for(int i = entities->size() - 1; i >= 0; i--)
    {
        //(*it)->tick(deltaTime);
		if(i >= entities->size()) continue;

		entities->at(i)->tick(deltaTime);
    }

    return true;
}

void EntityMgr::loadLevel()
{

}

void EntityMgr::selectFirstEntity()
{
    selectEntityAt(0);
}

void EntityMgr::selectNextEntity()
{
    selectEntityAt((selectedEntityIndex + 1) % entities->size());
}

void EntityMgr::selectEntityAt(int index)
{
    if (selectedEntity != NULL)
        selectedEntity->isSelected = false;

    selectedEntityIndex = index;
    selectedEntity = entities->at(index);

    selectedEntity->isSelected = true;
}

void EntityMgr::selectEntity(Entity* newEntity)
{
    if (selectedEntity == newEntity) return;

    if (selectedEntity != NULL)
    {
        selectedEntity->isSelected = false;
    }

    for (int i = 0; i < entities->size(); i++)
    {
        if (entities->at(i) == newEntity)
        {
            selectedEntityIndex = i;
            selectedEntity = newEntity;
            selectedEntity->isSelected = true;

            return;
        }
    }
}

Entity* EntityMgr::getEntityBySceneNode(Ogre::SceneNode* sceneNode)
{
    for (int i = 0; i < entities->size(); i++)
    {
        if (entities->at(i)->ogreSceneNode == sceneNode)
        {
            return entities->at(i);
        }
    }

    return NULL;
}

Entity* EntityMgr::createEntity(Entity* entity, Ogre::Vector3 position, Ogre::Vector3 direction)
{
    char nameBuffer[128];
    Ogre::String entityName;

    sprintf(nameBuffer, "%s%i", "Ship", entity->entityId);
    entityName = nameBuffer;

    entity->entityName = entityName;

	entity->position = position;
	entity->direction = direction;

    entity->ogreEntity = sceneMgr->createEntity(entity->meshFile);
    entity->ogreSceneNode = sceneMgr->getRootSceneNode()->createChildSceneNode(entityName);
    entity->ogreSceneNode->attachObject(entity->ogreEntity);

	entity->ogreSceneNode->setPosition(position);

    entities->push_back(entity);

	entity->awake();

    return entity;
}

void EntityMgr::removeEntity(Entity* entity)
{
	for(int i = entities->size() - 1; i >= 0; i--)
	{
		if(entity->entityId == entities->at(i)->entityId)
		{
			Ogre::String name = entities->at(i)->ogreSceneNode->getName();

			entity->isDestroyed = true;
			entities->erase(entities->begin() + i);

			if(entity == engine->gameMgr->player)
			{
				engine->gameMgr->player = NULL;
			}

			sceneMgr->getRootSceneNode()->removeAndDestroyChild(name);
			delete entity;
		}
	}
}