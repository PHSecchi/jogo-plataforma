#include "MapManager.h"

MapManager::MapManager(map <int, Tile*> tM, Map* m, sf::RenderWindow* window) :
	tilesMap(tM),
	mapPtr(m)
{
	if (mapPtr == nullptr)
	{
		cout << "mapPtr null in MapManager.cpp" << endl;
		exit(1);
	}

	backgroundPtr = nullptr;
	this->windowPtr = window;
}

MapManager::~MapManager()
{
	tilesMap.clear();
}

void MapManager::setMap(Map* map)
{
	mapPtr = map;
}

Map* MapManager::getMap() const
{
	return mapPtr;
}

void MapManager::setBackground(sf::Sprite* bg) {
	backgroundPtr = bg;
}

sf::Sprite* MapManager::getBackground() {
	return backgroundPtr;
}

void MapManager::draw()
{
	windowPtr->draw(*backgroundPtr);

	for (int i = 0; i < MAP_DIMENSION_X; i++)
	{
		for (int j = 0; j < MAP_DIMENSION_Y; j++)
		{
			Tile* tilePtr = nullptr;
			int k = mapPtr->getInfoMap(i, j).x + mapPtr->getInfoMap(i, j).y;
			tilePtr = tilesMap[k];
			tilePtr->setPosition(i * 96.f, j * 96.f);
			tilePtr->setRectTexture((mapPtr->getInfoXMap(i, j) * 16), (mapPtr->getInfoYMap(i, j) * 16));
			tilePtr->draw();
		}
	}
}

bool MapManager::areEntitiesColliding(sf::Vector2f entityPosition, sf::Vector2f entitySize, sf::Vector2f tilePosition)
{
	sf::Vector2f dist = entityPosition - tilePosition;

	if ((fabsf(dist.x) < ((entitySize.x + 96) / 2)) && (fabsf(dist.y) < ((entitySize.y + 96) / 2)))
		return true;

	return false;
}

vector<MapManager::TileInfo> MapManager::checkCollisions(sf::Vector2f entityPosition, sf::Vector2f entitySize)
{
	vector<MapManager::TileInfo> collisions;

	for (int i = 0; i < MAP_DIMENSION_X; i++)
	{
		for (int j = 0; j < MAP_DIMENSION_Y; j++)
		{
			int k = mapPtr->getInfoXMap(i, j) + mapPtr->getInfoYMap(i, j);

			Tile* tile = tilesMap[k];

			if (tile->getId() != IdsColidiveis::nonColliding)
			{
				sf::Vector2f p = sf::Vector2f(96.f * i + 96 / 2.f, 96.f * j + 96 / 2.f);
				tile->setPosition(p.x, p.y);

				if (areEntitiesColliding(entityPosition, entitySize, p))
					collisions.push_back({ tile, tile->getId(), tile->getPosition(), tile->getSize() });
			}
		}
	}

	return collisions;
}