#include "Throwable.h"

Throwable::Throwable(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Entity(ID, sz, pos, vel, texturePath, t, window)
{
}

Throwable::~Throwable()
{
}

void Throwable::draw()
{
	windowPtr->draw(body);
}