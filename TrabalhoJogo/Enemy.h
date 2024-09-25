#pragma once
#include "stdafx.h"
#include "Character.h"

class Enemy :
    public Character
{
protected:
    int enemyLevel;

public:
    Enemy(IdsColidiveis ID = IdsColidiveis::blank, sf::Vector2f sz = sf::Vector2f(96.f, 144.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), string texturePath = "", float* t = nullptr, sf::RenderWindow* window = nullptr);
    ~Enemy();

    virtual void draw() = 0;
    virtual void collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e) = 0;
    virtual void update() = 0;
    virtual void save() = 0;

    void setEnemyLevel(int enemyLevel);
};