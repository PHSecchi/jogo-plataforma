#include "stdafx.h"
#include "Entity.h"

Entity::Entity(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	body(sz),
	texture(),
	id(ID),
	position(pos),
	velocity(vel),
	sprite(),
	size(sz),
	destroy(false),
	flip(true)
{
	if (!texture.loadFromFile(texturePath))
	{
		cout << "Unable to load entity texture in \"Entity.cpp\"." << endl;
		exit(1);
	}

	sprite.setTexture(texture);
	sprite.setPosition(position);

	body.setTexture(sprite.getTexture());
	body.setOrigin(body.getSize() / 2.f);

	dt = t;
	windowPtr = window;
}

Entity::~Entity()
{
}

const IdsColidiveis Entity::getId()
{
	return id;
}

void Entity::setPosition(sf::Vector2f pos)
{
	position = pos;
	body.setPosition(position);
}

void Entity::setVelX(float x)
{
	velocity.x = x;
}

void Entity::setVelY(float y)
{
	velocity.y = y;
}

void Entity::turn()
{
	body.scale(sf::Vector2f(-1.f, 1.f));
	velocity.x = velocity.x * (-1);

	flip ? flip = false : flip = true;
}

sf::Vector2f Entity::getPosition()
{
	return position;
}

sf::Vector2f Entity::getSize()
{
	return size;
}

bool Entity::isGone() const
{
	return destroy;
}

bool Entity::getFlip()
{
	return flip;
}

void Entity::setFlip(bool f)
{
	if (!flip && !f)
		body.scale(sf::Vector2f(-1.f, 1.f));

	flip = f;
}

void Entity::clearSaveFiles()
{
	ofstream ofs;
	string files[5] = {
		"saves/Player.txt",
		"saves/Goblin.txt",
		"saves/BomberGoblin.txt",
		"saves/Boss.txt",
		"saves/Bomb.txt"
	};

	for (int i = 0; i < 5; i++)
	{
		ofs.open(files[i], ios::trunc);

		if (ofs.is_open())
		{
			ofs << "";
			ofs.close();
		}
		else
		{
			cout << "Unable to open \"" << files[i] << "\" in \"Entidade.cpp\"" << endl;
			exit(1);
		}
	}
}