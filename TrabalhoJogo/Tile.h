#pragma once
#include "stdafx.h"
#include "Entity.h"

class Tile:
	public Entity
{
public:
	Tile(IdsColidiveis ID = IdsColidiveis::blank, sf::Vector2f sz = sf::Vector2f(96.f, 96.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), string texturePath = "", float* t = nullptr, sf::RenderWindow* window = nullptr);
	~Tile();

	virtual void update();
	void draw();
	virtual void collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e) = 0;
	virtual void save();

	void setPosition(float x, float y);
	void setRectTexture(int x, int y);
	sf::Sprite getSprite();
};