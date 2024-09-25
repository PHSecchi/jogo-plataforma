#include "MagicalDoor.h"

MagicalDoor::MagicalDoor(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Tile(ID, sz, pos, vel, texturePath, t, window)
{
}

MagicalDoor::~MagicalDoor()
{
}

void MagicalDoor::collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e)
{
	sf::Vector2f distance = ePosition - position;
	sf::Vector2f gotInside;

	gotInside.x = fabsf(distance.x) - (eSize.x / 2 + size.x / 2);
	gotInside.y = fabsf(distance.y) - (eSize.y / 2 + size.y / 2);

	/* check if the entity really collided. */
	if (gotInside.x > 0.f && gotInside.y > 0.f)
		return;

	float gotInX = fabsf(gotInside.x);
	float gotInY = fabsf(gotInside.y);

	if (eId == IdsColidiveis::player || eId == IdsColidiveis::bomb)
		return;

	if (gotInX < gotInY) /* collided on the x-axis. */
	{
		if (distance.x > 0.f)
			ePosition.x = ePosition.x + gotInX;
		else
			ePosition.x = ePosition.x - gotInX;

		e->setPosition(ePosition);
		e->turn();
	}
	else /* collided on the y-axis. */
	{
		if (distance.y > 0.f)
			ePosition.y = ePosition.y + gotInY;
		else
			ePosition.y = ePosition.y - gotInY;

		e->setPosition(ePosition);
		e->setVelY(0.f);
	}
}