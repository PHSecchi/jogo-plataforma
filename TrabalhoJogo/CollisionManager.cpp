#include "CollisionManager.h"
#include "Throwable.h"

CollisionManager::CollisionManager() :
	list()
{
	mapManagerPtr = nullptr;
	entityListPtr = nullptr;
}

CollisionManager::~CollisionManager()
{
	list.clear();
	entityListPtr = nullptr;
	mapManagerPtr = nullptr;
}

void CollisionManager::setEntityList(EntityList* entityList)
{
	entityListPtr = entityList;
}

void CollisionManager::setMapManager(MapManager* mapManager)
{
	mapManagerPtr = mapManager;
}

void CollisionManager::addEntity(Entity* entity)
{
	list.insert(entity);
}

void CollisionManager::rmvEntity(Entity* entity)
{
	list.erase(entity);
}

void CollisionManager::clearEntities()
{
	Entity* pAux;
	set<Entity*> areGone;
	set<Entity*>::iterator it;

	for (it = list.begin(); it != list.end(); it++)
	{
		pAux = *it;

		if (pAux->isGone())
			areGone.insert(pAux);
	}

	for (it = areGone.begin(); it != areGone.end(); it++)
	{
		pAux = *it;
		rmvEntity(pAux);
		entityListPtr->removeAndDestroy(pAux);
	}

	areGone.clear();
}

void CollisionManager::clearWholeList()
{
	list.clear();
}

void CollisionManager::checkCollisions()
{
	set<Entity*>::iterator setIt;
	set<Entity*>::iterator setIt2;

	for (setIt = list.begin(); setIt != list.end(); setIt++)
	{
		Entity* e1 = *setIt;
		vector<MapManager::TileInfo> tilesColliding = mapManagerPtr->checkCollisions(e1->getPosition(), e1->getSize());

		for (auto colisao : tilesColliding)
		{
			e1->collide(colisao.id, colisao.position, colisao.size, colisao.tilePtr);
			colisao.tilePtr->setPosition(colisao.position.x, colisao.position.y);
			colisao.tilePtr->collide(e1->getId(), e1->getPosition(), e1->getSize(), e1);
		}

		setIt2 = setIt;
		setIt2++;

		for (; setIt2 != list.end(); setIt2++)
		{
			Entity* e2 = *setIt2;

			if (areEntitiesColliding(e1, e2))
			{
				e1->collide(e2->getId(), e2->getPosition(), e2->getSize(), e2);
				e2->collide(e1->getId(), e1->getPosition(), e1->getSize(), e1);
			}
		}
	}

	clearEntities();
}

bool CollisionManager::areEntitiesColliding(Entity* e1, Entity* e2)
{
	sf::Vector2f e1Position = e1->getPosition();
	sf::Vector2f e2Position = e2->getPosition();
	sf::Vector2f e1Size = e1->getSize();
	sf::Vector2f e2Size = e2->getSize();
	sf::Vector2f distance = e1Position - e2Position;

	if (fabsf(distance.x) < ((e1Size.x + e2Size.x) / 2) && fabsf(distance.y) < ((e1Size.y + e2Size.y) / 2))
		return true;

	return false;
}

/* returns true if list is empty. */
bool CollisionManager::operator!()
{
	return list.empty();
}