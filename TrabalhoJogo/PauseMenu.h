#pragma once
#include "Menu.h"
#include "stdafx.h"

#define PAUSEMENU_MAX_ITEMS 4

class StateManager;
class GraphicsManager;
class MainMenu;

class PauseMenu :
	public Menu
{
private:
	sf::Text menuOptions[PAUSEMENU_MAX_ITEMS];
	MainMenu* mainMenuPtr;
public:
	PauseMenu(StateManager* stateManager = nullptr, GraphicsManager* graphicsManager = nullptr, string bgPath = "", sf::RenderWindow* window = nullptr);
	~PauseMenu();

	void draw();

	void moveUp();
	void moveDown();
	void selectOption();
	void update(sf::Event event);

	void setMainMenu(MainMenu* mainMenu);
};