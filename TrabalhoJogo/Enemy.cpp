#include "Enemy.h"

Enemy::Enemy(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Character(ID, sz, pos, vel, texturePath, t, window),
	enemyLevel(1)
{
}

Enemy::~Enemy()
{
}

void Enemy::setEnemyLevel(int enemyLevel)
{
	this->enemyLevel = enemyLevel;
}
