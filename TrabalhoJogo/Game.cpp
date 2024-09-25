#include "stdafx.h"
#include "Game.h"

Game::Game() :
	stateManager(),
	graphicsManager(),
	updateManager(),
	collisionManager(),
	mainMenu(&stateManager, &graphicsManager, "assets/background/main_menu_bg.jpg", graphicsManager.getWindow()),
	level1("assets/maps/level1/tiles.png", "assets/maps/level1/map.txt", "assets/maps/level1/background.png", sf::Vector2f(28.5 * 96.f, 3 * 96.f), updateManager.getTime(), graphicsManager.getWindow()),
	level2("assets/maps/level2/tiles.png", "assets/maps/level2/map.txt", "assets/maps/level2/background.png", sf::Vector2f(27.5 * 96.f, 2.0 * 96.f), updateManager.getTime(), graphicsManager.getWindow()),
	level3("assets/maps/level3/tiles.png", "assets/maps/level3/map.txt", "assets/maps/level3/background.png", sf::Vector2f(28.5 * 96.f, 28.0 * 96.f), updateManager.getTime(), graphicsManager.getWindow())
{
	playerPtr = nullptr;
	playerPtr = new Warrior(IdsColidiveis::player, sf::Vector2f(118.f, 144.f), sf::Vector2f(400.f, 400.f), sf::Vector2f(0.f, 0.f), "assets/characters/player/warrior.png", updateManager.getTime(), graphicsManager.getWindow());
	initManagers();
	initLevels();
}

Game::~Game()
{
	delete playerPtr;
}

void Game::run()
{
	srand(static_cast<unsigned int>(time(NULL)));

	while (graphicsManager.windowIsRunning())
	{
		/* checks if menu is active, which level is being played and if it has been finished. */
		stateManager.checkStatus();

		/* the time spent in each iteration of the loop is saved and the clock is reset. */
		updateManager.restartClock();

		graphicsManager.setEvent();
		graphicsManager.clear();

		updateManager.update();

		/* do not check for collisions when the menu is active. */
		if (!stateManager.getMainMenuStatus())
			collisionManager.checkCollisions();

		/* if playing, draw map and entities. If the menu is active, draw the menu. */
		graphicsManager.draw();

		/* window.display */
		graphicsManager.render();
	}
}

/* init the managers */
void Game::initManagers()
{
	updateManager.setStateManager(&stateManager);

	graphicsManager.setMenu(&mainMenu);
	graphicsManager.setStateManager(&stateManager);
	graphicsManager.setPlayer(playerPtr);

	stateManager.setMainMenu(&mainMenu);
	stateManager.setManagers(&graphicsManager, &updateManager, &collisionManager);
	stateManager.setLevels(&level1, &level2, &level3);
	stateManager.setPlayer(playerPtr);
}

/* init the levels */
void Game::initLevels()
{
	level1.setCollisionManager(&collisionManager);
	level2.setCollisionManager(&collisionManager);
	level3.setCollisionManager(&collisionManager);

	level1.createMap();
	level2.createMap();
	level3.createMap();
}