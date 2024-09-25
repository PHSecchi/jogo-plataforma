#include "Slime.h"

Slime::Slime(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Obstacle(ID, sz, pos, vel, texturePath, t, window)
{
}

Slime::~Slime()
{
}

void Slime::collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e)
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

	if (eId == IdsColidiveis::player)
	{
		if (gotInX < gotInY) /* the player collided on the x-axis. */
		{

			if (distance.x > 0.f)
				ePosition.x += gotInX; /* if the player collided on the right side of the slime. */
			else
				ePosition.x -= gotInX; /* else the player collided on the left side of the slime. */

			e->setPosition(ePosition);
			e->setVelX(0.f);
		}
		else /* the player collided on the y-axis. */
		{
			if (distance.y > 0.f)
				ePosition.y += gotInY; /* if the player collided on the underside of the slime */
			else
			{
				ePosition.y -= gotInY; /* else the player collided on the top side of the slime. */
				Player* player = static_cast<Player*>(e);
				player->setCanJump(false);
			}

			e->setPosition(ePosition);
			e->setVelY(0.f);
		}
	}
	else if (eId == IdsColidiveis::goblin || eId == IdsColidiveis::bomberGoblin)
	{
		if (gotInX < gotInY) /* the entity collided on the x-axis. */
		{

			if (distance.x > 0.f)
				ePosition.x += gotInX; /* if the entity collided on the right side of the slime. */
			else
				ePosition.x -= gotInX; /* else the entity collided on the left side of the slime. */

			e->setPosition(ePosition);
		}
		else /* the entity collided on the y-axis. */
		{
			if (distance.y > 0.f)
				ePosition.y += gotInY; /* if the entity collided on the underside of the slime. */
			else
				ePosition.y -= gotInY; /* else the entity collided on the top side of the slime. */

			e->setPosition(ePosition);
			e->setVelY(0.f);
		}
	}
}