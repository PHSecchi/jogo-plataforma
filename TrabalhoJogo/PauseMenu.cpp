#include "stdafx.h"
#include "PauseMenu.h"
#include "StateManager.h"
#include "GraphicsManager.h"
#include "MainMenu.h"

PauseMenu::PauseMenu(StateManager* stateManager, GraphicsManager* graphicsManager, string bgPath, sf::RenderWindow* window):
	Menu(stateManager, graphicsManager, bgPath, window),
	menuOptions()
{
	mainMenuPtr = nullptr;

	if (!titleFont.loadFromFile("assets/fonts/Dimitri.ttf"))
	{
		cout << "Unable to load title font in \"PauseMenu.cpp\"" << endl;
		exit(1);
	}

	if (!itemFont.loadFromFile("assets/fonts/Dimitri.ttf"))
	{
		cout << "Unable to load item font in \"PauseMenu.cpp\"" << endl;
		exit(1);
	}

	sf::FloatRect textRect;

	menuOptions[0].setFont(titleFont);
	menuOptions[0].setCharacterSize(104);
	menuOptions[0].setFillColor(sf::Color::Yellow);
	menuOptions[0].setString("Paused");
	textRect = menuOptions[0].getLocalBounds();
	menuOptions[0].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[0].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (PAUSEMENU_MAX_ITEMS + 1) * 1.5f));

	menuOptions[1].setFont(itemFont);
	menuOptions[1].setCharacterSize(54);
	menuOptions[1].setFillColor(sf::Color::White);
	menuOptions[1].setString("Resume");
	textRect = menuOptions[1].getLocalBounds();
	menuOptions[1].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[1].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (PAUSEMENU_MAX_ITEMS + 1) * 2.25));

	menuOptions[2].setFont(itemFont);
	menuOptions[2].setCharacterSize(54);
	menuOptions[2].setFillColor(sf::Color::White);
	menuOptions[2].setString("Save");
	textRect = menuOptions[2].getLocalBounds();
	menuOptions[2].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[2].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (PAUSEMENU_MAX_ITEMS + 1) * 3.25));

	menuOptions[3].setFont(itemFont);
	menuOptions[3].setCharacterSize(54);
	menuOptions[3].setFillColor(sf::Color::White);
	menuOptions[3].setString("Back to main menu");
	textRect = menuOptions[3].getLocalBounds();
	menuOptions[3].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[3].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (PAUSEMENU_MAX_ITEMS + 1) * 4.25));
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::draw()
{
	windowPtr->draw(background);

	for (int i = 0; i < PAUSEMENU_MAX_ITEMS; i++)
		windowPtr->draw(menuOptions[i]);
}

void PauseMenu::moveUp()
{
	/* there is the title at 0 index . */
	if (selectedOption - 1 >= 1)
	{
		menuOptions[selectedOption].setFillColor(sf::Color::White);
		selectedOption--;
		menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
	}
}

void PauseMenu::moveDown()
{
	if (selectedOption + 1 < PAUSEMENU_MAX_ITEMS)
	{
		menuOptions[selectedOption].setFillColor(sf::Color::White);
		selectedOption++;
		menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
	}
}

void PauseMenu::selectOption()
{
	switch (selectedOption)
	{
	case 1: // resume game selected
		stateManagerPtr->setMainMenuStatus(false);
		break;

	case 2: // save game selected
		stateManagerPtr->saveGame();
		break;

	case 3: // back to main menu selected
		graphicsManagerPtr->setMenu(mainMenuPtr);
		stateManagerPtr->clearCollisionManagerList();
		stateManagerPtr->restartLevels();
		break;
	}
}

void PauseMenu::update(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up)
			moveUp();
		if (event.key.code == sf::Keyboard::Down)
			moveDown();
		if (event.key.code == sf::Keyboard::Return)
			selectOption();
		if (event.key.code == sf::Keyboard::Escape)
			stateManagerPtr->setMainMenuStatus(false);
	}
}

void PauseMenu::setMainMenu(MainMenu* mainMenu)
{
	if (mainMenu != nullptr)
		mainMenuPtr = mainMenu;
	else
	{
		cout << "Unable to set \"mainMenu\" in \"PauseMenu.cpp\": null pointer" << endl;
		exit(1);
	}
}