#include "Goblin.h"

Goblin::Goblin(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Enemy(ID, sz, pos, vel, texturePath, t, window),
	haste(1.2f)
{
}

Goblin::~Goblin()
{
}

void Goblin::update()
{
	velocity.y += 9.81f;
	position += velocity * (*dt);
	body.setPosition(position);
}

void Goblin::draw()
{
	windowPtr->draw(body);
}

void Goblin::collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e)
{
	if (eId == IdsColidiveis::player)
	{
		if (enemyLevel <= 5)
		{
			velocity *= haste;
			enemyLevel++;
		}
	}

	if (eId == IdsColidiveis::magicalDoor)
	{
		destroy = true;
	}
}

void Goblin::save()
{
	/* all output operations happen at the end of the file, appending to its existing contents. */
	ofstream ofs("saves/Goblin.txt", ios::app);

	if (ofs.is_open())
	{
		ofs << position.x << ' ' << position.y << ' ' << velocity.x << ' ' << velocity.y << ' ' << size.x + 25.f << ' ' <<
			size.y + 15.f << ' ' << flip << ' ' << hp << ' ' << enemyLevel << ' ' << haste << endl;

		ofs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Goblin.txt\" in \"Goblin.cpp\"" << endl;
		exit(1);
	}
}

void Goblin::setHaste(float haste)
{
	this->haste = haste;
}