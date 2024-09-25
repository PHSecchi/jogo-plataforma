#include "Level3.h"

Level3::Level3(string tilePath, string mapPath, string bgPath, sf::Vector2f point, float* t, sf::RenderWindow* window):
	Level(tilePath, mapPath, bgPath, point, t, window, 3)
{
}

Level3::~Level3()
{
	if (player != nullptr)
		entityListPtr->removeEntity(player);

	if (!entityListPtr->isEmpty())
		entityListPtr->destroyEntities();

	delete entityListPtr;
	delete tilesMap[0];
	delete tilesMap[1];
	delete tilesMap[2];
	delete tilesMap[3];
	delete tilesMap[4];
}

void Level3::setPlayerPosition()
{
	player->restart();
	player->setPosition(sf::Vector2f(3.5 * 96.f, 5 * 96.f));
}

const sf::Vector2f Level3::getEndPoint() const
{
	return endPoint;
}

void Level3::createEnemies()
{
	int qntd = rand() % 3 + 5;

	cout << qntd << endl;

	for (int i = 0; i < qntd; i++)
	{
		float px = static_cast<float>(rand() % 2400 + 200);
		float py = static_cast<float>(rand() % 2400 + 200);

		Goblin* goblinPtr = new Goblin(IdsColidiveis::goblin, sf::Vector2f(96.f, 144.f), sf::Vector2f(px, py), sf::Vector2f(50.f, 50.f), "assets/characters/enemyGoblin/goblin.png", dt, windowPtr);
		entityListPtr->includeEntity(goblinPtr);
		collisionManagerPtr->addEntity(goblinPtr);
	}

	qntd = rand() % 3 + 5;

	for (int i = 0; i < qntd; i++)
	{
		float px = static_cast<float>(rand() % 2400 + 200);
		float py = static_cast<float>(rand() % 2400 + 200);

		BomberGoblin* bomberGoblinPtr = new BomberGoblin(IdsColidiveis::bomberGoblin, sf::Vector2f(96.f, 144.f), sf::Vector2f(px, py), sf::Vector2f(80.f, 80.f), "assets/characters/enemyBomberGoblin/bomberGoblin.png", dt, windowPtr);
		entityListPtr->includeEntity(bomberGoblinPtr);
		collisionManagerPtr->addEntity(bomberGoblinPtr);
		bomberGoblinPtr->setEntityList(entityListPtr);
		bomberGoblinPtr->setCollisionManager(collisionManagerPtr);
	}

	Boss* bossPtr = new Boss(IdsColidiveis::boss, sf::Vector2f(288.f, 432.f), sf::Vector2f(1120.f, 2060.f), sf::Vector2f(0.f, 0.f), "assets/characters/enemyBoss/boss.png", dt, windowPtr, 3.f);
	entityListPtr->includeEntity(bossPtr);
	collisionManagerPtr->addEntity(bossPtr);
	bossPtr->setEntityList(entityListPtr);
	bossPtr->setCollisionManager(collisionManagerPtr);
}

void Level3::createObstacles()
{
	// have to think about.
}

void Level3::initTiles(string tilePath)
{
	Tile* tilePtr = nullptr;

	tilePtr = new Trap(IdsColidiveis::trap, sf::Vector2f(96.f, 96.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), tilePath, dt, windowPtr);
	tilesMap[1] = tilePtr;

	tilePtr = new Slime(IdsColidiveis::slime, sf::Vector2f(96.f, 96.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), tilePath, dt, windowPtr);
	tilesMap[4] = tilePtr;
}

void Level3::retrieveEntities()
{
	/* opens file for reading */
	ifstream ifs("saves/Goblin.txt", ios::in);

	if (ifs.is_open())
	{
		Goblin* goblinPtr;

		sf::Vector2f position, velocity, size;
		bool flip;
		int hp, enemyLevel;
		float haste;

		while (!ifs.eof())
		{
			ifs >> position.x >> position.y >> velocity.x >> velocity.y
				>> size.x >> size.y >> flip >> hp >> enemyLevel >> haste;

			goblinPtr = new Goblin(IdsColidiveis::goblin, size, position, velocity, "assets/characters/enemyGoblin/goblin.png", dt, windowPtr);

			goblinPtr->setFlip(flip);
			goblinPtr->setHp(hp);
			goblinPtr->setEnemyLevel(enemyLevel);
			goblinPtr->setHaste(haste);

			entityListPtr->includeEntity(goblinPtr);
			collisionManagerPtr->addEntity(goblinPtr);
		}

		ifs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Goblin.txt\" in \"Level3.cpp\"" << endl;
		exit(1);
	}

	/* opens file for reading */
	ifs.open("saves/BomberGoblin.txt", ios::in);

	if (ifs.is_open())
	{
		BomberGoblin* bomberGoblinPtr;

		sf::Vector2f position, velocity, size;
		bool flip, canThrow;
		int hp, enemyLevel;
		float limit, cooldown, bombSize;

		while (!ifs.eof())
		{
			ifs >> position.x >> position.y >> velocity.x >> velocity.y
				>> size.x >> size.y >> flip >> hp >> enemyLevel >> limit >> cooldown >> canThrow >> bombSize;

			bomberGoblinPtr = new BomberGoblin(IdsColidiveis::bomberGoblin, size, position, velocity, "assets/characters/enemyBomberGoblin/bomberGoblin.png", dt, windowPtr, bombSize);

			bomberGoblinPtr->setFlip(flip);
			bomberGoblinPtr->setHp(hp);
			bomberGoblinPtr->setEnemyLevel(enemyLevel);
			bomberGoblinPtr->setLimit(limit);
			bomberGoblinPtr->setCooldown(cooldown);
			bomberGoblinPtr->setCanThrow(canThrow);
			bomberGoblinPtr->setBombSize(bombSize);
			bomberGoblinPtr->setEntityList(entityListPtr);
			bomberGoblinPtr->setCollisionManager(collisionManagerPtr);

			entityListPtr->includeEntity(bomberGoblinPtr);
			collisionManagerPtr->addEntity(bomberGoblinPtr);
		}

		ifs.close();
	}
	else
	{
		cout << "Unable to open \"saves/BomberGoblin.txt\" in \"Level3.cpp\"" << endl;
		exit(1);
	}

	/* opens file for reading */
	ifs.open("saves/Boss.txt", ios::in);

	if (ifs.is_open())
	{
		Boss* bossPtr;

		sf::Vector2f position, velocity, size;
		bool flip, canThrow;
		int hp, enemyLevel;
		float limit, cooldown, bombSize;

		while (!ifs.eof())
		{
			ifs >> position.x >> position.y >> velocity.x >> velocity.y
				>> size.x >> size.y >> flip >> hp >> enemyLevel >> limit >> cooldown >> canThrow >> bombSize;

			bossPtr = new Boss(IdsColidiveis::boss, size, position, velocity, "assets/characters/enemyBoss/boss.png", dt, windowPtr, bombSize);

			if (!flip)
				bossPtr->setFlip(flip);
			else
				bossPtr->setFlip(!flip);

			bossPtr->setHp(hp);
			bossPtr->setEnemyLevel(enemyLevel);
			bossPtr->setLimit(limit);
			bossPtr->setCooldown(cooldown);
			bossPtr->setCanThrow(canThrow);
			bossPtr->setBombSize(bombSize);
			bossPtr->setEntityList(entityListPtr);
			bossPtr->setCollisionManager(collisionManagerPtr);

			entityListPtr->includeEntity(bossPtr);
			collisionManagerPtr->addEntity(bossPtr);
		}

		ifs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Boss.txt\" in \"Level3.cpp\"" << endl;
		exit(1);
	}

	/* opens file for reading */
	ifs.open("saves/Bomb.txt", ios::in);

	if (ifs.is_open())
	{
		Bomb* bombPtr;

		sf::Vector2f position, velocity, size;
		bool flip;

		while (!ifs.eof())
		{
			ifs >> position.x >> position.y >> velocity.x >> velocity.y
				>> size.x >> size.y >> flip;

			bombPtr = new Bomb(IdsColidiveis::bomb, size, position, velocity, "assets/characters/enemyBomberGoblin/bomb.png", dt, windowPtr);
			bombPtr->setFlip(flip);
			entityListPtr->includeEntity(bombPtr);
			collisionManagerPtr->addEntity(bombPtr);
		}

		ifs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Bomb.txt\" in \"Level3.cpp\"" << endl;
		exit(1);
	}
}