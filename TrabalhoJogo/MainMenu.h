#pragma once
#include"stdafx.h"
#include"Menu.h"
#include "GraphicsManager.h"
#include "LevelMenu.h"
#include "PauseMenu.h"
#include "Ranking.h"

#define MAINMENU_MAX_ITEMS 4

class MainMenu :
	public Menu
{
private:
	sf::Text menuOptions[MAINMENU_MAX_ITEMS];
	LevelMenu levelMenu;
	PauseMenu pauseMenu;
	Ranking ranking;

public:
	MainMenu(StateManager* stateManager = nullptr, GraphicsManager* graphicsManager = nullptr, string bgPath = "", sf::RenderWindow* window = nullptr);
	~MainMenu();

	void draw();
	void moveUp();
	void moveDown();
	void selectOption();
	void update(sf::Event event);

	Menu* getPauseMenu();
	Menu* getLevelMenu();
	Ranking* getRankingMenu();
};