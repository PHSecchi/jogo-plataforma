#include "stdafx.h"
#include "GraphicsManager.h"
#include "StateManager.h"
#include "Menu.h"

GraphicsManager::GraphicsManager() :
	window(sf::VideoMode(1280, 720), " Green Threat"),
	event(),
	view(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(1920.0f, 1080.0f))
{
	stateManagerPtr = nullptr;
	mapManagerPtr = nullptr;

	window.setVerticalSyncEnabled(1);
	window.setFramerateLimit(50);

	menuPtr = nullptr;

	playerPtr = nullptr;
	entityListPtr = nullptr;
}

GraphicsManager::~GraphicsManager()
{
	mapManagerPtr = nullptr;
	stateManagerPtr = nullptr;

	menuPtr = nullptr;

	entityListPtr = nullptr;
	playerPtr = nullptr;
}

void GraphicsManager::draw()
{
	if (stateManagerPtr->getMainMenuStatus())
	{
		window.setView(window.getDefaultView());
		menuPtr->draw();
	}
	else
	{
		mapManagerPtr->draw();
		updateView();
		entityListPtr->draw();
	}
}

void GraphicsManager::updateView()
{
	sf::Vector2f view_pos = playerPtr->getPosition();

	float x = view_pos.x;
	float y = view_pos.y;

	x = std::floorf(x);
	y = std::floorf(y);

	x += 0.375f;
	y += 0.375f;

	view.setCenter(x, y);

	if ((view_pos.x - 1920 / 2) < 0)
		view.move(sf::Vector2f((-1) * (view_pos.x - 1920 / 2), 0.f));

	if ((view_pos.x + 1920 / 2) > 2880)
		view.move(sf::Vector2f(2880 - (view_pos.x + 1920 / 2), 0.f));

	if ((view_pos.y - 1080 / 2) < 0)
		view.move(sf::Vector2f(0.f, (-1) * (view_pos.y - 1080 / 2)));

	if ((view_pos.y + 1080 / 2) > 2880)
		view.move(sf::Vector2f(0.f, 2880 - (view_pos.y + 1080 / 2)));

	window.setView(view);
}

void GraphicsManager::setEntityList(EntityList* entityList)
{
	entityListPtr = entityList;
}

void GraphicsManager::setMenu(Menu* menu)
{
	if (menu != nullptr)
		menuPtr = menu;
	else
	{
		cout << "Unable to set \"menu\" in \"GraphicsManager.cpp\": null pointer" << endl;
		exit(1);
	}
}

void GraphicsManager::closeWindow()
{
	window.close();
}

void GraphicsManager::clear()
{
	window.clear();
}

void GraphicsManager::render()
{
	window.display();
}

void GraphicsManager::setStateManager(StateManager* stateManager)
{
	if (stateManager != nullptr)
		stateManagerPtr = stateManager;
	else
	{
		cout << "Unable to set \"stateManager\" in \"GraphicsManager.cpp\": null pointer" << endl;
		exit(1);
	}
}

/* checa o evento do topo de eventos e realiza a acao correspondente ao evento. */
void GraphicsManager::setEvent()
{
	if (this->window.pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			window.close();

		if (stateManagerPtr->getMainMenuStatus())
			menuPtr->update(this->event);
		else
		{
			if (this->event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape)
					stateManagerPtr->setMainMenuStatus(true);
			}
		}
	}
}

bool GraphicsManager::windowIsRunning()
{
	return window.isOpen();
}

sf::RenderWindow* GraphicsManager::getWindow()
{
	return &window;
}

void GraphicsManager::setMapManager(MapManager* mapManager)
{
	mapManagerPtr = mapManager;
}

void GraphicsManager::setPlayer(Player* player)
{
	playerPtr = player;
}