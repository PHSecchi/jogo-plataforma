#include "Obstacle.h"

Obstacle::Obstacle(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Tile(ID, sz, pos, vel, texturePath, t, window)
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::update()
{
}

void Obstacle::save()
{
}