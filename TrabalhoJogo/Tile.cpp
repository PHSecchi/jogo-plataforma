#include "Tile.h"

Tile::Tile(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Entity(ID, sz, pos, vel, texturePath, t, window)
{
}

Tile::~Tile()
{
}

void Tile::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	position.x = x;
	position.y = y;
}

void Tile::setRectTexture(int x, int y)
{
	sprite.setTextureRect(sf::IntRect(x, y, 16, 16));
	sprite.setScale(sf::Vector2f(6, 6));
}

sf::Sprite Tile::getSprite()
{
	return sprite;
}

void Tile::draw()
{
	windowPtr->draw(sprite);
}

void Tile::save()
{
}

void Tile::update()
{
}