#include "UpdateManager.h"
#include "StateManager.h"

UpdateManager::UpdateManager() :
	clock(),
	dt(0.f)
{
	stateManagerPtr = nullptr;
	entityListPtr = nullptr;
	levelPtr = nullptr;
	clock.restart();
}

UpdateManager::~UpdateManager()
{
	stateManagerPtr = nullptr;
	entityListPtr = nullptr;
	levelPtr = nullptr;
}

void UpdateManager::setStateManager(StateManager* stateManager)
{
	if (stateManager != nullptr)
		stateManagerPtr = stateManager;
	else
	{
		cout << "Unable to set \"stateManagerPtr\" in \"UpdateManager.cpp\": null pointer" << endl;
		exit(1);
	}
}

void UpdateManager::setEntityList(EntityList* entityList)
{
	if (entityList != nullptr)
		entityListPtr = entityList;
	else
	{
		cout << "Unable to set \"entityListPtr\" in \"UpdateManager.cpp\": null pointer" << endl;
		exit(1);
	}
}

void UpdateManager::restartClock()
{
	dt = clock.restart().asSeconds();
}

void UpdateManager::update()
{
	if (!stateManagerPtr->getMainMenuStatus())
	{
		entityListPtr->update();

		if (!(levelPtr->isAlive()))
			levelPtr->setPlayerPosition();

		if (calcDistance(levelPtr->getPlayerPosition(), levelPtr->getEndPoint()) <= 96)
			levelPtr->setCompletedStatus(true);
	}
}

void UpdateManager::setLevel(Level* level)
{
	if (level != nullptr)
		levelPtr = level;
	else
	{
		cout << "Unable to set \"level\" in \"UpdateManager.cpp\": null pointer" << endl;
		exit(1);
	}
}

float* UpdateManager::getTime()
{
	return &dt;
}

float UpdateManager::calcDistance(sf::Vector2f pj, sf::Vector2f pf)
{
	float d, dx, dy;

	dx = (pj.x - pf.x);
	dy = (pj.y - pf.y);

	d = sqrt(dx * dx + dy * dy);

	return d;
}