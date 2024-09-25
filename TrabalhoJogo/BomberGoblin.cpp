#include "BomberGoblin.h"

BomberGoblin::BomberGoblin(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window, float bombSz) :
	Enemy(ID, sz, pos, vel, texturePath, t, window),
	Thrower(6.f),
	bombSize(bombSz)
{
}

BomberGoblin::~BomberGoblin()
{
}

void BomberGoblin::update()
{
	cooldown += *dt;
	canThrow(cooldown);

	if (canThrowBool)
	{
		throwBomb();
		canThrowBool = false;
		cooldown = 0.f;
	}

	velocity.y += 9.81f;
	position += velocity * (*dt);
	body.setPosition(position);
}

void BomberGoblin::draw()
{
	windowPtr->draw(body);
}

void BomberGoblin::collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e)
{
	if (eId == IdsColidiveis::player)
	{
		if (enemyLevel <= 5)
		{
			limit -= 0.4f;
			enemyLevel++;
		}
	}

	if (eId == IdsColidiveis::magicalDoor)
	{
		destroy = true;
	}
}

void BomberGoblin::throwBomb()
{
	Bomb* bombPtr = nullptr;

	if (flip)
		bombPtr = new Bomb(IdsColidiveis::bomb, sf::Vector2f(28.f, 28.f) * bombSize, position, sf::Vector2f(200.f, -200.f), "assets/characters/enemyBomberGoblin/bomb.png", dt, windowPtr);
	else
		bombPtr = new Bomb(IdsColidiveis::bomb, sf::Vector2f(28.f, 28.f) * bombSize, position, sf::Vector2f(-200.f, -200.f), "assets/characters/enemyBomberGoblin/bomb.png", dt, windowPtr);

	entityListPtr->includeEntity(bombPtr);
	collisionManagerPtr->addEntity(bombPtr);
}

void BomberGoblin::save()
{
	/* all output operations happen at the end of the file, appending to its existing contents. */
	ofstream ofs("saves/BomberGoblin.txt", ios::app);

	if (ofs.is_open())
	{
		ofs << position.x << ' ' << position.y << ' ' << velocity.x << ' ' << velocity.y << ' ' << size.x + 25.f << ' ' <<
			size.y + 15.f << ' ' << flip << ' ' << hp << ' ' << enemyLevel << ' ' << limit << ' ' << cooldown << ' ' << canThrowBool << ' ' << bombSize << endl;

		ofs.close();
	}
	else
	{
		cout << "Unable to open \"saves/BomberGoblin.txt\" in \"BomberGoblin.cpp\"" << endl;
		exit(1);
	}
}

void BomberGoblin::setBombSize(float bombSize)
{
	this->bombSize = bombSize;
}