#pragma once
#include "stdafx.h"
#include "Character.h"
#include "Trap.h"

class Player :
	public Character
{
protected:
	float slowness;
	bool alive;
	bool canJump;
	float jumpHeight;
	float score;
	int currentPunishment;
	int prevPunishment;

public:
	Player(IdsColidiveis ID = IdsColidiveis::blank, sf::Vector2f sz = sf::Vector2f(60.f, 90.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), string texturePath = "", float* t = nullptr, sf::RenderWindow* window = nullptr);
	~Player();

	virtual void update() = 0;
	void draw();
	void collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e);
	void save();
	void die();
	void die(Entity* e);
	bool isAlive();
	void restart();
	void setCanJump(bool canJump);
	void load(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f size, bool flip, bool canJump, int hp, int prevPunishment, int currentPunishment, float jumpHeight, float score);
	void punish();
	float getScore();
	int getCurrentPunishment();
	int getPrevPunishment();
	void resetScore();
};