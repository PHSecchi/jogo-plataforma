#include "Warrior.h"

Warrior::Warrior(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Player(ID, sz, pos, vel, texturePath, t, window),
	limit(0.3f),
	canAttackBool(false),
	cooldown(0.f)
{
}

Warrior::~Warrior()
{
}

void Warrior::canAttack(float t)
{
	if (t >= limit)
		canAttackBool = true;
}

void Warrior::update()
{
	cooldown += *dt;
	canAttack(cooldown);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		velocity.x = -600.f / slowness;
		body.setScale(sf::Vector2f(-1.f, 1.f));
		flip = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		velocity.x = 600.f / slowness;
		body.setScale(sf::Vector2f(1.f, 1.f));
		flip = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;
		velocity.y = -sqrt(250.0f * 98.0f * jumpHeight);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canAttackBool)
	{
		canAttackBool = false;
		
		/* it is not attacking yet! */

		cooldown = 0.f;
	}

	velocity.x *= 0.9f;
	velocity.y += 98.1f;

	position += velocity * (*dt);
	body.setPosition(position);
}