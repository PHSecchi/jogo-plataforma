#pragma once
#include "stdafx.h"
#include "Level.h"
#include "Player.h"

class UpdateManager;
class GraphicsManager;
class MainMenu;

class StateManager
{
private:
	MainMenu* mainMenuPtr;
	bool mainMenuStatus;

	GraphicsManager* graphicsManagerPtr;
	UpdateManager* updateManagerPtr;
	CollisionManager* collisionManagerPtr;

	Player* playerPtr;

	Level* level1Ptr;
	Level* level2Ptr;
	Level* level3Ptr;
	bool level1Status;
	bool level2Status;
	bool level3Status;

	/* private methods because it is only used for organizing StateManager.cpp */
	Level* getLevel(int levelNum);
	void setLevelStatusTrue(int levelNum);

public:
	StateManager();
	~StateManager();

	void checkStatus();

	void setMainMenu(MainMenu* mainMenu);
	void setLevels(Level* level1, Level* level2, Level* level3);
	void setManagers(GraphicsManager* graphicsManager, UpdateManager* updateManager, CollisionManager* collisionManager);
	void setPlayer(Player* player);

	void initLevel1();
	void initLevel2();
	void initLevel3();

	void saveGame();
	void initSavedLevel();
	void restartLevels();

	void clearCollisionManagerList();

	void setMainMenuStatus(bool mainMenuStatus);
	bool getMainMenuStatus() const;
};