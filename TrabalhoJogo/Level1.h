#pragma once
#include "stdafx.h"
#include "Level.h"

class Level1 :
	public Level
{
public:
	Level1(string tilePath = "", string mapPath = "", string bgPath = "", sf::Vector2f point = sf::Vector2f(0.f, 0.f), float* t = nullptr, sf::RenderWindow* window = nullptr);
	~Level1();

	void setPlayerPosition();
	const sf::Vector2f getEndPoint() const;
	void createEnemies();
	void createObstacles();
	void initTiles(string tilePath);
	void retrieveEntities();
};