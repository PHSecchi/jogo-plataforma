#include "Menu.h"
#include "GraphicsManager.h"

Menu::Menu(StateManager* stateManager, GraphicsManager* graphicsManager, string bgPath, sf::RenderWindow* window):
	titleFont(),
	itemFont(),
	texture(),
	background(),
	selectedOption(1)
{
	if (!texture.loadFromFile(bgPath))
	{
		cout << "Unable to load the background texture in \"Menu.cpp\": does " << bgPath << " exist?" << endl;
		exit(1);
	}

	sf::Vector2f rectangleSize = static_cast<sf::Vector2f>(window->getSize());
	background.setSize(rectangleSize);
	background.setTexture(&texture);
	background.setOrigin(0.0f, 0.0f);

	stateManagerPtr = stateManager;
	graphicsManagerPtr = graphicsManager;

	windowPtr = window;
}

Menu::~Menu()
{
}