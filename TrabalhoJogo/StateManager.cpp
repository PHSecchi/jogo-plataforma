#include "stdafx.h"
#include "StateManager.h"
#include "GraphicsManager.h"
#include "UpdateManager.h"
#include "MainMenu.h"

StateManager::StateManager():
	level1Status(false),
	level2Status(false),
	level3Status(false),
	mainMenuStatus(true)
{
	graphicsManagerPtr = nullptr;
	updateManagerPtr = nullptr;
	collisionManagerPtr = nullptr;

	level1Ptr = nullptr;
	level2Ptr = nullptr;
	level3Ptr = nullptr;

	mainMenuPtr = nullptr;

	playerPtr = nullptr;
}

StateManager::~StateManager()
{
	graphicsManagerPtr = nullptr;
	updateManagerPtr = nullptr;
	collisionManagerPtr = nullptr;

	level1Ptr = nullptr;
	level2Ptr = nullptr;
	level3Ptr = nullptr;

	mainMenuPtr = nullptr;

	playerPtr = nullptr;
}

void StateManager::initLevel1()
{
	level1Ptr->initLevel(playerPtr);

	graphicsManagerPtr->setEntityList(level1Ptr->getEntityList());
	graphicsManagerPtr->setMapManager(level1Ptr->getMapManager());

	collisionManagerPtr->setMapManager(level1Ptr->getMapManager());

	updateManagerPtr->setLevel(level1Ptr);
	updateManagerPtr->setEntityList(level1Ptr->getEntityList());

	level1Status = true;
	level2Status = false;
	level3Status = false;
	mainMenuStatus = false;
}

void StateManager::initLevel2()
{
	level2Ptr->initLevel(playerPtr);

	graphicsManagerPtr->setEntityList(level2Ptr->getEntityList());
	graphicsManagerPtr->setMapManager(level2Ptr->getMapManager());

	collisionManagerPtr->setMapManager(level2Ptr->getMapManager());

	updateManagerPtr->setLevel(level2Ptr);
	updateManagerPtr->setEntityList(level2Ptr->getEntityList());

	level1Status = false;
	level2Status = true;
	level3Status = false;
	mainMenuStatus = false;
}

void StateManager::initLevel3()
{
	level3Ptr->initLevel(playerPtr);

	graphicsManagerPtr->setEntityList(level3Ptr->getEntityList());
	graphicsManagerPtr->setMapManager(level3Ptr->getMapManager());

	collisionManagerPtr->setMapManager(level3Ptr->getMapManager());

	updateManagerPtr->setLevel(level3Ptr);
	updateManagerPtr->setEntityList(level3Ptr->getEntityList());

	level1Status = false;
	level2Status = false;
	level3Status = true;
	mainMenuStatus = false;
}

void StateManager::restartLevels()
{
	level1Ptr->restartLevel();
	level2Ptr->restartLevel();
	level3Ptr->restartLevel();
}

void StateManager::clearCollisionManagerList()
{
	collisionManagerPtr->clearWholeList();
}

void StateManager::setLevels(Level* level1, Level* level2, Level* level3)
{
	level1Ptr = level1;
	level2Ptr = level2;
	level3Ptr = level3;
}

void StateManager::setManagers(GraphicsManager* graphicsManager, UpdateManager* updateManager, CollisionManager* collisionManager)
{
	if (graphicsManager != nullptr && updateManager != nullptr && collisionManager != nullptr)
	{
		graphicsManagerPtr = graphicsManager;
		updateManagerPtr = updateManager;
		collisionManagerPtr = collisionManager;
	}
	else
	{
		cout << "Unable to set \"managers\" in \"StateManager.cpp\": null pointers" << endl;
		exit(1);
	}
}

void StateManager::setPlayer(Player* player)
{
	playerPtr = player;
}

void StateManager::checkStatus()
{
	if (mainMenuStatus) /* currently on the menu. */
		return;

	if (level1Status) /* currently playing level 1. */
	{
		/* when level 1 ends, clear it and go to level 2. */
		if (level1Ptr->getCompletedStatus())
		{
			level1Status = false;
			level2Status = false;
			level3Status = false;
			mainMenuStatus = false;
			collisionManagerPtr->clearWholeList();
			initLevel2();
		}
	}
	else if (level2Status) /* currently playing level 2. */
	{
		/* when level 2 ends, clear it and go to level 3. */
		if (level2Ptr->getCompletedStatus())
		{
			level1Status = false;
			level2Status = false;
			level3Status = false;
			mainMenuStatus = false;
			collisionManagerPtr->clearWholeList();
			initLevel3();
		}
	}
	else if (level3Status) /* currently playing level 3. */
	{
		/* when level 3 ends, clear it and show the ranking. */
		if (level3Ptr->getCompletedStatus())
		{
			level1Status = false;
			level2Status = false;
			level3Status = false;
			mainMenuStatus = true;

			mainMenuPtr->getRankingMenu()->setPlayer(playerPtr);
			graphicsManagerPtr->setMenu(mainMenuPtr->getRankingMenu());

			collisionManagerPtr->clearWholeList();
			restartLevels();
		}
	}
}

void StateManager::setMainMenu(MainMenu* mainMenu)
{
	if (mainMenu != nullptr)
	{
		mainMenuPtr = mainMenu;
	}
	else
	{
		cout << "Unable to set \"mainMenu\" in \"StateManager.cpp\": null pointer" << endl;
		exit(1);
	}
}

bool StateManager::getMainMenuStatus() const
{
	return mainMenuStatus;
}

void StateManager::setMainMenuStatus(bool mainMenuStatus)
{
	this->mainMenuStatus = mainMenuStatus;
}

void StateManager::saveGame()
{
	if (level1Status)
		level1Ptr->save();
	else if (level2Status)
		level2Ptr->save();
	else if (level3Status)
		level3Ptr->save();
}

Level* StateManager::getLevel(int levelNum)
{
	if (levelNum == 1)
		return level1Ptr;
	else if (levelNum == 2)
		return level2Ptr;
	else if (levelNum == 3)
		return level3Ptr;
	else
	{
		cout << "Unable to get level " << levelNum << " in \"StateManager.cpp\": level number does not exist" << endl;
		exit(1);
	}
}

void StateManager::setLevelStatusTrue(int levelNum)
{
	if (levelNum == 1)
		level1Status = true;
	else if (levelNum == 2)
		level2Status = true;
	else if (levelNum == 3)
		level3Status = true;
	else
	{
		cout << "Unable to set level " << levelNum << " status in \"StateManager.cpp\": level number does not exist" << endl;
		exit(1);
	}
}

void StateManager::initSavedLevel()
{
	/* opens file for reading */
	ifstream ifs("saves/Level.txt", ios::in);

	if (ifs.is_open())
	{
		int levelNum;
		/* puts the saved level number in levelNum. */
		ifs >> levelNum;

		/* gets the level and init it. */
		Level* level = getLevel(levelNum);

		level->initSavedLevel(playerPtr);

		graphicsManagerPtr->setEntityList(level->getEntityList());
		graphicsManagerPtr->setMapManager(level->getMapManager());

		collisionManagerPtr->setMapManager(level->getMapManager());

		updateManagerPtr->setLevel(level);
		updateManagerPtr->setEntityList(level->getEntityList());

		setLevelStatusTrue(levelNum);
		setMainMenuStatus(false);

		ifs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Level.txt\" in \"StateManager.cpp\"" << endl;
		exit(1);
	}
}