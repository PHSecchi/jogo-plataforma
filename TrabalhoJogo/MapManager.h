#pragma once
#include "stdafx.h"
#include "Map.h"
#include "Tile.h"
#include "Entity.h"
#include <map>

class MapManager
{
private:
	Map* mapPtr;
	sf::Sprite* backgroundPtr;
	sf::RenderWindow* windowPtr;
	map <int, Tile*> tilesMap;

public:

	typedef struct tileInfo {
		Tile* tilePtr;
		const IdsColidiveis id;
		sf::Vector2f position;
		sf::Vector2f size;
	} TileInfo;

	MapManager(map <int, Tile*> tM = {}, Map* m = nullptr, sf::RenderWindow* window = nullptr);
	~MapManager();

	void setMap(Map* map);
	Map* getMap() const;

	void setBackground(sf::Sprite* background);
	sf::Sprite* getBackground();

	void draw();

	vector<tileInfo> checkCollisions(sf::Vector2f entityPosition, sf::Vector2f entitySize);
	bool areEntitiesColliding(sf::Vector2f entityPosition, sf::Vector2f entitySize, sf::Vector2f tilePosition);
};