#include "Bomb.h"

Bomb::Bomb(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Throwable(ID, sz, pos, vel, texturePath, t, window)
{
}

Bomb::~Bomb()
{
}

/* bomb gets vanished when colliding with tiles. */
void Bomb::collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e)
{
	if (eId != IdsColidiveis::nonColliding &&
		eId != IdsColidiveis::bomb &&
		eId != IdsColidiveis::bomberGoblin &&
		eId != IdsColidiveis::goblin &&
		eId != IdsColidiveis::boss)
	{
		destroy = true;
	}
}

void Bomb::update()
{
	velocity.y += 9.81f / 2;
	position += velocity * (*dt);
	body.setPosition(position);
}

void Bomb::save()
{
	/* all output operations happen at the end of the file, appending to its existing contents. */
	ofstream ofs("saves/Bomb.txt", ios::app);

	if (ofs.is_open())
	{
		ofs << position.x << ' ' << position.y << ' ' << velocity.x << ' ' << velocity.y << ' ' << size.x << ' ' <<
			size.y << ' ' << flip << endl;

		ofs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Bomb.txt\" in \"Bomb.cpp\"" << endl;
		exit(1);
	}
}