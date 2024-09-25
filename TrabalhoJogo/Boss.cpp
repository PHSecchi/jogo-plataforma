#include "Boss.h"

Boss::Boss(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window, float bombSz):
	BomberGoblin(ID, sz, pos, vel, texturePath, t, window, bombSz)
{
	hp = 500;
	setFlip(false);
}

Boss::~Boss()
{
}

void Boss::collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e)
{
}

void Boss::throwBomb()
{
	Bomb* bombPtr = nullptr;
	bombPtr = new Bomb(IdsColidiveis::bomb, sf::Vector2f(28.f, 28.f) * bombSize, position, sf::Vector2f(-200, -200), "assets/characters/enemyBoss/bomb.png", dt, windowPtr);

	entityListPtr->includeEntity(bombPtr);
	collisionManagerPtr->addEntity(bombPtr);
}

void Boss::save()
{
	/* Any contents that existed in the file before it is open are discarded. */
	ofstream ofs("saves/Boss.txt", ios::trunc);

	if (ofs.is_open())
	{
		ofs << position.x << ' ' << position.y << ' ' << velocity.x << ' ' << velocity.y << ' ' << size.x + 25.f << ' ' <<
			size.y + 15.f << ' ' << flip << ' ' << hp << ' ' << enemyLevel << ' ' << limit << ' ' << cooldown << ' ' << canThrowBool << ' ' << bombSize << endl;

		ofs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Boss.txt\" in \"Boss.cpp\"" << endl;
		exit(1);
	}
}