#pragma once
#include "stdafx.h"
#include "EntityList.h"
#include "Menu.h"
#include "MapManager.h"
#include "Player.h"

class Menu;
class StateManager;

class GraphicsManager
{
private:
	StateManager* stateManagerPtr;
	MapManager* mapManagerPtr;

	Menu* menuPtr;
	sf::RenderWindow window;
	sf::Event event;
	sf::View view;

	Player* playerPtr;
	EntityList* entityListPtr;
public:
	GraphicsManager();
	~GraphicsManager();

	void draw();
	void clear();
	void render();
	void updateView();
	void closeWindow();

	bool windowIsRunning();
	sf::RenderWindow* getWindow();

	void setMapManager(MapManager* mapManager);
	void setStateManager(StateManager* stateManager);

	void setEntityList(EntityList* entityList);
	void setMenu(Menu* menu);
	void setEvent();
	
	void setPlayer(Player* player);
};