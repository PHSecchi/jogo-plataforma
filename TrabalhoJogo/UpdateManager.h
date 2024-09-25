#pragma once
#include "stdafx.h"
#include "EntityList.h"
#include "Entity.h"
#include "Level.h"
#include "Menu.h"
#include "GraphicsManager.h"

class StateManager;

class UpdateManager
{
private:
	StateManager* stateManagerPtr;
	EntityList* entityListPtr;
	Level* levelPtr;
	sf::Clock clock;
	float dt;

public:
	UpdateManager();
	~UpdateManager();

	void setStateManager(StateManager* stateManager);
	void setEntityList(EntityList* entityList);
	void restartClock();
	void update();
	void setLevel(Level* level);
	float* getTime();
	float calcDistance(sf::Vector2f pj, sf::Vector2f pf);
};