#include "Character.h"

Character::Character(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window) :
	Entity(ID, sz, pos, vel, texturePath, t, window),
	hp(100)
{
}

Character::Character(int hp, IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Entity(ID, sz, pos, vel, texturePath, t, window)
{
	this->hp = hp;
}

Character::~Character()
{
}

void Character::setHp(int hp)
{
	this->hp = hp;
}

void Character::operator+(int i)
{
	setHp(i);
}