#include "stdafx.h"
#include "LevelMenu.h"
#include "MainMenu.h"
#include "LevelMenu.h"

LevelMenu::LevelMenu(StateManager* stateManager, GraphicsManager* graphicsManager, string bgPath, sf::RenderWindow* window):
	Menu(stateManager, graphicsManager, bgPath, window),
	menuOptions()
{
	mainMenuPtr = nullptr;
	
	if (!titleFont.loadFromFile("assets/fonts/Dimitri.ttf"))
	{
		cout << "Unable to load title font in \"LevelMenu.cpp\"" << endl;
		exit(1);
	}

	if (!itemFont.loadFromFile("assets/fonts/Dimitri.ttf"))
	{
		cout << "Unable to load item font in \"LevelMenu.cpp\"" << endl;
		exit(1);
	}

	sf::FloatRect textRect;

	menuOptions[0].setFont(titleFont);
	menuOptions[0].setCharacterSize(80);
	menuOptions[0].setFillColor(sf::Color::White);
	menuOptions[0].setString("Choose the level");
	textRect = menuOptions[0].getLocalBounds();
	menuOptions[0].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[0].setPosition(sf::Vector2f((WIDTH / 2.f), HEIGHT / (LEVELMENU_MAX_ITEMS + 1) * 1.5));

	menuOptions[1].setFont(itemFont);
	menuOptions[1].setCharacterSize(54);
	menuOptions[1].setFillColor(sf::Color::Yellow);
	menuOptions[1].setString("Level 1");
	textRect = menuOptions[1].getLocalBounds();
	menuOptions[1].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[1].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (LEVELMENU_MAX_ITEMS + 1) * 2.25));

	menuOptions[2].setFont(itemFont);
	menuOptions[2].setCharacterSize(54);
	menuOptions[2].setFillColor(sf::Color::White);
	menuOptions[2].setString("Level 2");
	textRect = menuOptions[2].getLocalBounds();
	menuOptions[2].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[2].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (LEVELMENU_MAX_ITEMS + 1) * 3.25));

	menuOptions[3].setFont(itemFont);
	menuOptions[3].setCharacterSize(54);
	menuOptions[3].setFillColor(sf::Color::White);
	menuOptions[3].setString("Level 3");
	textRect = menuOptions[3].getLocalBounds();
	menuOptions[3].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[3].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (LEVELMENU_MAX_ITEMS + 1) * 4.25));

	menuOptions[4].setFont(itemFont);
	menuOptions[4].setCharacterSize(54);
	menuOptions[4].setFillColor(sf::Color::White);
	menuOptions[4].setString("Back to main menu");
	textRect = menuOptions[4].getLocalBounds();
	menuOptions[4].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[4].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (LEVELMENU_MAX_ITEMS + 1) * 5.25));
}

LevelMenu::~LevelMenu()
{
}

void LevelMenu::draw()
{
	windowPtr->draw(background);

	for (int i = 0; i < LEVELMENU_MAX_ITEMS; i++)
		windowPtr->draw(menuOptions[i]);
}

void LevelMenu::moveUp()
{
	/* there is the title at 0 index . */
	if (selectedOption - 1 >= 1)
	{
		menuOptions[selectedOption].setFillColor(sf::Color::White);
		selectedOption--;
		menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
	}
}

void LevelMenu::moveDown()
{
	if (selectedOption + 1 < LEVELMENU_MAX_ITEMS)
	{
		menuOptions[selectedOption].setFillColor(sf::Color::White);
		selectedOption++;
		menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
	}
}

void LevelMenu::selectOption()
{
	switch (selectedOption)
	{
	case 1: // level 1 selected
		graphicsManagerPtr->setMenu(mainMenuPtr->getPauseMenu());
		stateManagerPtr->initLevel1();
		break;

	case 2: // level 2 selected
		graphicsManagerPtr->setMenu(mainMenuPtr->getPauseMenu());
		stateManagerPtr->initLevel2();
		break;

	case 3: // level 3 selected
		graphicsManagerPtr->setMenu(mainMenuPtr->getPauseMenu());
		stateManagerPtr->initLevel3();
		break;

	case 4: // return selected
		graphicsManagerPtr->setMenu(mainMenuPtr);
		break;
	}
}

/* menu navigation */
void LevelMenu::update(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up)
			moveUp();
		if (event.key.code == sf::Keyboard::Down)
			moveDown();
		if (event.key.code == sf::Keyboard::Return)
			selectOption();
	}
}

void LevelMenu::setMainMenu(MainMenu* mainMenu)
{
	if (mainMenu != nullptr)
		mainMenuPtr = mainMenu;
	else
	{
		cout << "Unable to set \"mainMenu\" in \"LevelMenu.cpp\": null pointer" << endl;
		exit(1);
	}
}