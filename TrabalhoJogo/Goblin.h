#pragma once
#include "stdafx.h"
#include "Enemy.h"

class Goblin :
	public Enemy
{
private:
	float haste;
public:
	Goblin(IdsColidiveis ID = IdsColidiveis::blank, sf::Vector2f sz = sf::Vector2f(96.f, 144.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), string texturePath = "", float* t = nullptr, sf::RenderWindow* window = nullptr);
	~Goblin();

	void update();
	void draw();
	void collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e);
	void save();

	void setHaste(float haste);
};