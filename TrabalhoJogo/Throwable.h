#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "EntityList.h"
#include "CollisionManager.h"

class Throwable :
	public Entity
{
public:
	Throwable(IdsColidiveis ID = IdsColidiveis::blank, sf::Vector2f sz = sf::Vector2f(28.f, 28.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), string texturePath = "", float* t = nullptr, sf::RenderWindow* window = nullptr);
	~Throwable();

	virtual void update() = 0;
	void draw();
	virtual void collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e) = 0;
	virtual void save() = 0;
};