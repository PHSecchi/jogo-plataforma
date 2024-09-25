#pragma once
#include "stdafx.h"
#include "EntityList.h"
#include "Player.h"
#include "MapManager.h"
#include "CollisionManager.h"
#include "Map.h"
#include "Goblin.h"
#include "BomberGoblin.h"
#include "Tile.h"
#include "Block.h"
#include "MagicalDoor.h"
#include "Slime.h"
#include "Air.h"
#include "Spike.h"
#include <map>

class Level
{
protected:
	const int levelNum;
	bool completedStatus;
	const sf::Vector2f endPoint;
	float* dt;

	EntityList* entityListPtr;
	Player* player;

	sf::RenderWindow* windowPtr;

	CollisionManager* collisionManagerPtr;
	MapManager* mapManagerPtr;

	Map* mapPtr;
	map<int, Tile*> tilesMap;

	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	string tilePath;
	string mapPath;
	string bgPath;
public:
	Level(string tilePath = "", string mapPath = "", string bgPath = "", sf::Vector2f point = sf::Vector2f(0.f, 0.f), float* t = nullptr, sf::RenderWindow* window = nullptr, int lN = 0);
	~Level();

	virtual void initTiles(string tilePath) = 0;
	virtual void createObstacles() = 0;
	virtual void createEnemies() = 0;
	virtual void setPlayerPosition() = 0;
	virtual const sf::Vector2f getEndPoint() const = 0;
	virtual void retrieveEntities() = 0;

	EntityList* getEntityList();

	void setPlayer(Player* player);
	void setPlayerPosition(sf::Vector2f position);
	sf::Vector2f getPlayerPosition() const;
	bool isAlive();

	void setCompletedStatus(bool status);
	const bool getCompletedStatus() const;

	void initLevel(Player* player);
	void restartLevel();

	void createMap();
	void deleteTiles();

	MapManager* getMapManager();
	void setCollisionManager(CollisionManager* collisionManager);

	void save();
	void retrievePlayer();
	void initSavedLevel(Player* player);
};