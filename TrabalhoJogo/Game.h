#pragma once
#include "stdafx.h"
#include "GraphicsManager.h"
#include "UpdateManager.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Warrior.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "MainMenu.h"

class Game
{
private:
	GraphicsManager graphicsManager;
	UpdateManager updateManager;
	StateManager stateManager;
	CollisionManager collisionManager;

	MainMenu mainMenu;

	Player* playerPtr;

	Level1 level1;
	Level2 level2;
	Level3 level3;
public:
	Game();
	~Game();

	void run();
	void initManagers();
	void initLevels();
};