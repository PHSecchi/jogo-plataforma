#pragma once
#include "stdafx.h"
#include "Tile.h"

class Obstacle :
    public Tile
{
public:
    Obstacle(IdsColidiveis ID = IdsColidiveis::blank, sf::Vector2f sz = sf::Vector2f(96.f, 96.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), string texturePath = "", float* t = nullptr, sf::RenderWindow* window = nullptr);
    ~Obstacle();

    virtual void update();
    void collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e) = 0;
    virtual void save();
};