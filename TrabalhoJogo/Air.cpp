#include "Air.h"

Air::Air(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Tile(ID, sz, pos, vel, texturePath, t, window)
{
}

Air::~Air()
{
}

/* since it's air, nothing should happen when colliding :p */
void Air::collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e)
{
}