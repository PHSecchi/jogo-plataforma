#pragma once
#include "stdafx.h"

class Entity
{
protected:
	sf::RenderWindow* windowPtr;
	sf::RectangleShape body;
	sf::Texture texture;
	sf::Vector2f velocity;
	const IdsColidiveis id;
	sf::Sprite sprite;
	sf::Vector2f position;
	sf::Vector2f size;
	
	float* dt;
	bool destroy;
	bool flip;

public:
	Entity(IdsColidiveis ID = IdsColidiveis::blank, sf::Vector2f sz = sf::Vector2f(96.f, 144.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), string texturePath = "", float* t = nullptr, sf::RenderWindow* window = nullptr);
	~Entity();

	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e) = 0;
	virtual void save() = 0;

	const IdsColidiveis getId();

	bool getFlip();
	void setFlip(bool f);
	void turn();

	void setPosition(sf::Vector2f pos);
	void setVelX(float x);
	void setVelY(float y);

	sf::Vector2f getPosition();
	sf::Vector2f getSize();

	bool isGone() const;
	void clearSaveFiles();
};