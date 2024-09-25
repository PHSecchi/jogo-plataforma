#pragma once
#include "stdafx.h"
#include "Menu.h"
#include "GraphicsManager.h"

#define LEVELMENU_MAX_ITEMS 5

class MainMenu;

class LevelMenu :
	public Menu
{
private:
	sf::Text menuOptions[LEVELMENU_MAX_ITEMS];
	MainMenu* mainMenuPtr;
public:
	LevelMenu(StateManager* stateManager = nullptr, GraphicsManager* graphicsManager = nullptr, string bgPath = "", sf::RenderWindow* window = nullptr);
	~LevelMenu();

	void draw();

	void moveUp();
	void moveDown();
	void selectOption();
	void update(sf::Event event);

	void setMainMenu(MainMenu* mainMenu);
};