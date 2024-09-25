#pragma once
#include "stdafx.h"
#include "Enemy.h"
#include "Thrower.h"
#include "Bomb.h"

class BomberGoblin :
	public Enemy, public Thrower
{
protected:
	float bombSize;
public:
	BomberGoblin(IdsColidiveis ID = IdsColidiveis::blank, sf::Vector2f sz = sf::Vector2f(96.f, 144.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), string texturePath = "", float* t = nullptr, sf::RenderWindow* window = nullptr, float bombSz = 1.f);
	~BomberGoblin();

	void draw();
	virtual void collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e);
	void update();
	virtual void save();

	virtual void throwBomb();
	void setBombSize(float bombSize);
};