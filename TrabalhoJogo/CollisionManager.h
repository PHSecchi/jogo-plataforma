#pragma once
#include "stdafx.h"
#include <set>
#include <list>
#include "MapManager.h"
#include "Entity.h"
#include "EntityList.h"
#include <math.h>

class Throwable;

class CollisionManager
{
private:
	set<Entity*> list;
	MapManager* mapManagerPtr;
	EntityList* entityListPtr;

public:
	CollisionManager();
	~CollisionManager();

	void setMapManager(MapManager* mapManager);
	void setEntityList(EntityList* entityList);

	void addEntity(Entity* entity);
	void rmvEntity(Entity* entity);
	void clearEntities();
	void clearWholeList();

	void checkCollisions();
	bool areEntitiesColliding(Entity* e1, Entity* e2);
	bool operator !();
};