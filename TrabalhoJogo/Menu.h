#pragma once
#include "stdafx.h"
#include "StateManager.h"

#define WIDTH 1280.f
#define HEIGHT 720.f

class GraphicsManager;

class Menu
{
protected:
	sf::Font titleFont;
	sf::Font itemFont;
	sf::Texture texture;
	sf::RectangleShape background;

	int selectedOption;

	StateManager* stateManagerPtr;
	GraphicsManager* graphicsManagerPtr;
	sf::RenderWindow* windowPtr;

public:
	Menu(StateManager* stateManager = nullptr, GraphicsManager* graphicsManager = nullptr, string bgPath = "", sf::RenderWindow* window = nullptr);
	~Menu();

	virtual void draw() = 0;

	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
	virtual void selectOption() = 0;
	virtual void update(sf::Event event) = 0;
};