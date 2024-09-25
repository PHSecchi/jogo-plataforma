#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MainMenu(StateManager* stateManager, GraphicsManager* graphicsManager, string bgPath, sf::RenderWindow* window):
	Menu(stateManager, graphicsManager, bgPath, window),
	menuOptions(),
	levelMenu(stateManager, graphicsManager, bgPath, window),
	pauseMenu(stateManager, graphicsManager, bgPath, window),
	ranking(stateManager, graphicsManager, bgPath, window)
{
	try
	{
		if (!titleFont.loadFromFile("assets/fonts/Dimitri.ttf"))
			throw 1;
	}
	catch (int e)
	{
		if (e == 1)
			cout << "Unable to load font in \"MainMenu.cpp\"" << endl;
		exit(1);
	}

	if (!itemFont.loadFromFile("assets/fonts/Dimitri.ttf"))
	{
		cout << "Unable to load item font in \"MainMenu.cpp\"" << endl;
		exit(1);
	}

	sf::FloatRect textRect;

	menuOptions[0].setFont(titleFont);
	menuOptions[0].setCharacterSize(104);
	menuOptions[0].setFillColor(sf::Color::White);
	menuOptions[0].setString(" Green Threat");
	textRect = menuOptions[0].getLocalBounds();
	menuOptions[0].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[0].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (MAINMENU_MAX_ITEMS + 1) * 1.5));

	menuOptions[1].setFont(itemFont);
	menuOptions[1].setCharacterSize(54);
	menuOptions[1].setFillColor(sf::Color::Yellow);
	menuOptions[1].setString("Play");
	textRect = menuOptions[1].getLocalBounds();
	menuOptions[1].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[1].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (MAINMENU_MAX_ITEMS + 1) * 2.25));

	menuOptions[2].setFont(itemFont);
	menuOptions[2].setCharacterSize(54);
	menuOptions[2].setFillColor(sf::Color::White);
	menuOptions[2].setString("Load");
	textRect = menuOptions[2].getLocalBounds();
	menuOptions[2].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[2].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (MAINMENU_MAX_ITEMS + 1) * 3.25));

	menuOptions[3].setFont(itemFont);
	menuOptions[3].setCharacterSize(54);
	menuOptions[3].setFillColor(sf::Color::White);
	menuOptions[3].setString("Quit");
	textRect = menuOptions[3].getLocalBounds();
	menuOptions[3].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[3].setPosition(sf::Vector2f(WIDTH / 2.f, HEIGHT / (MAINMENU_MAX_ITEMS + 1) * 4.25));

	levelMenu.setMainMenu(this);
	pauseMenu.setMainMenu(this);
	ranking.setMainMenu(this);
}

MainMenu::~MainMenu()
{
}

void MainMenu::draw()
{
	windowPtr->draw(background);

	for (int i = 0; i < MAINMENU_MAX_ITEMS; i++)
		windowPtr->draw(menuOptions[i]);
}

void MainMenu::moveUp()
{
	/* there is the game name at 0 index . */
	if (selectedOption - 1 >= 1)
	{
		menuOptions[selectedOption].setFillColor(sf::Color::White);
		selectedOption--;
		menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
	}
}

void MainMenu::moveDown()
{
	if (selectedOption + 1 < MAINMENU_MAX_ITEMS)
	{
		menuOptions[selectedOption].setFillColor(sf::Color::White);
		selectedOption++;
		menuOptions[selectedOption].setFillColor(sf::Color::Yellow);
	}
}

void MainMenu::update(sf::Event event)
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

void MainMenu::selectOption()
{
	switch (selectedOption)
	{
	case 1: /* play selected */
		graphicsManagerPtr->setMenu(&levelMenu);
		break;

	case 2: /* load game selected */
		graphicsManagerPtr->setMenu(&pauseMenu);
		stateManagerPtr->initSavedLevel();
		break;

	case 3: /* quit selected */
		graphicsManagerPtr->closeWindow();
		break;
	}
}

Menu* MainMenu::getLevelMenu()
{
	return &levelMenu;
}

Menu* MainMenu::getPauseMenu()
{
	return &pauseMenu;
}

Ranking* MainMenu::getRankingMenu()
{
	return &ranking;
}