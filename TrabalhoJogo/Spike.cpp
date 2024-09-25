#include "Spike.h"

Spike::Spike(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Obstacle(ID, sz, pos, vel, texturePath, t, window)
{
}

Spike::~Spike()
{
}

void Spike::collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e)
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

	if (eId == IdsColidiveis::goblin || eId == IdsColidiveis::bomberGoblin)
	{
		if (gotInX < gotInY)
		{
			if (distance.x > 0.f)
				ePosition.x += gotInX; /* collided on the right side of the spike. */
			else
				ePosition.x -= gotInX; /* collided on the left side of the spike. */

			e->setPosition(ePosition);
			e->turn();
		}
		else
		{
			if (distance.y > 0.f)
				ePosition.y = ePosition.y + gotInY; /* collided on the underside of the slime. */
			else
				ePosition.y = ePosition.y - gotInY; /* collided on the top side of the slime. */

			e->setPosition(ePosition);
			e->setVelY(0.f);
		}
	}
}