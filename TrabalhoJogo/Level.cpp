#include "Level.h"

Level::Level(string tilePath, string mapPath, string bgPath, sf::Vector2f point, float* t, sf::RenderWindow* window, int lN):
	entityListPtr(),
	completedStatus(false),
	endPoint(point),
	tilesMap(),
	levelNum(lN)
{
	dt = t;
	windowPtr = window;
	
	player = nullptr;
	entityListPtr = new EntityList();

	collisionManagerPtr = nullptr;
	mapManagerPtr = nullptr;
	mapPtr = nullptr;

	if (!tilePath.empty() || !mapPath.empty() || !bgPath.empty())
	{
		this->tilePath = tilePath;
		this->mapPath = mapPath;
		this->bgPath = bgPath;
	}
	else
	{
		cout << "Unable to set \"tilePath\" or \"mapPath\" or \"bgPath\" in \"Level.cpp\": string is empty" << endl;
		exit(1);
	}
}

Level::~Level()
{
	delete (mapPtr);
	mapPtr = nullptr;

	delete (mapManagerPtr);
	mapManagerPtr = nullptr;
}

/* returns 1 if alive, 0 if dead. */
bool Level::isAlive()
{
	if (player->isAlive())
		return true;
	else
		return false;
}

void Level::setPlayer(Player* player)
{
	this->player = player;
	entityListPtr->includeEntity(this->player);
}

EntityList* Level::getEntityList()
{
	return entityListPtr;
}

void Level::setPlayerPosition(sf::Vector2f position)
{
	player->restart();
	player->setPosition(position);
}

void Level::createMap()
{
	Tile* tilePtr = nullptr;

	tilePtr = new Block(IdsColidiveis::block, sf::Vector2f(96.f, 96.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), tilePath, dt, windowPtr);
	tilesMap[0] = tilePtr;
	tilePtr = new MagicalDoor(IdsColidiveis::magicalDoor, sf::Vector2f(96.f, 96.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), tilePath, dt, windowPtr);
	tilesMap[2] = tilePtr;
	tilePtr = new Air(IdsColidiveis::nonColliding, sf::Vector2f(96.f, 96.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), tilePath, dt, windowPtr);
	tilesMap[3] = tilePtr;

	initTiles(tilePath);

	mapPtr = new Map(mapPath);
	mapManagerPtr = new MapManager(tilesMap, mapPtr, windowPtr);

	if (bgTexture.loadFromFile(bgPath))
	{
		bgSprite.setTexture(bgTexture);
		bgSprite.setPosition(sf::Vector2f(0.f, 0.f));
		bgSprite.setScale(sf::Vector2f(1.f, 1.f));

		mapManagerPtr->setBackground(&bgSprite);
	}
	else
	{
		cout << "Unable to load \"bgPath\" in \"Level.cpp\"" << endl;
		exit(1);
	}
}

/* sets player, creates enemies and obstacles. */
void Level::initLevel(Player* player)
{
	setPlayer(player);
	player->restart();

	collisionManagerPtr->addEntity(player);
	collisionManagerPtr->setEntityList(entityListPtr);

	createObstacles();
	createEnemies();
	setPlayerPosition();
}

/* destroys all entities on the level. */
void Level::restartLevel()
{
	completedStatus = false;
	if (!entityListPtr->isEmpty())
	{
		player->restart();
		entityListPtr->removeEntity(player);

		player = nullptr;

		if (!entityListPtr->isEmpty())
			entityListPtr->destroyEntities();
	}
}

void Level::setCompletedStatus(bool status)
{
	completedStatus = status;
}

const bool Level::getCompletedStatus() const
{
	return completedStatus;
}

sf::Vector2f Level::getPlayerPosition() const
{
	return player->getPosition();
}

const sf::Vector2f Level::getEndPoint() const
{
	return endPoint;
}

MapManager* Level::getMapManager()
{
	return mapManagerPtr;
}

void Level::setCollisionManager(CollisionManager* collisionManager)
{
	collisionManagerPtr = collisionManager;
}

/* destroys the tiles map. */
void Level::deleteTiles()
{
	Tile* tilePtr = nullptr;

	for (auto iterador = tilesMap.begin(); iterador != tilesMap.end(); iterador++)
	{
		tilePtr = (*iterador).second;
		delete tilePtr;
	}

	tilesMap.clear();
}

void Level::save()
{
	/* previous content is deleted and replaced by the new one. */
	ofstream ofs("saves/Level.txt", ios::trunc);

	if (ofs.is_open())
	{
		ofs << levelNum;
		ofs.close();
		entityListPtr->save();
	}
	else
	{
		cout << "Unable to open \"saves/Level.txt\" in \"Level.cpp\"" << endl;
		exit(1);
	}
}

/* initializes the level reading the saved attributes and loading them into entities. */
void Level::initSavedLevel(Player* player)
{
	/* get saved attributes and set the player. */
	setPlayer(player);
	retrievePlayer();
	this->player->restart();

	collisionManagerPtr->addEntity(this->player);
	collisionManagerPtr->setEntityList(entityListPtr);

	retrieveEntities();
}

/* opens file, reads the saved attributes and load them into the player.  */
void Level::retrievePlayer()
{
	/* opens file for reading */
	ifstream ifs("saves/Player.txt", ios::in);

	if (ifs.is_open())
	{
		sf::Vector2f position, velocity, size;
		bool flip, canJump;
		int hp, prevPunishment, currentPunishment;
		float jumpHeight, score;
		int vezesLoop = 1;

		ifs >> position.x >> position.y >> velocity.x >> velocity.y >> size.x >>
			size.y >> flip >> hp >> canJump >> jumpHeight >> prevPunishment >> currentPunishment >> score;

		player->load(position, velocity, size, flip, canJump, hp, prevPunishment, currentPunishment, jumpHeight, score);

		ifs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Player.txt\" in \"Level.cpp\"" << endl;
		exit(1);
	}
}