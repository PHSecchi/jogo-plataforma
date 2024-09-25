#pragma once
#include "stdafx.h"
#include "Throwable.h"

class Bomb :
    public Throwable
{
public:
    Bomb(IdsColidiveis ID = IdsColidiveis::blank, sf::Vector2f sz = sf::Vector2f(28.f, 28.f), sf::Vector2f pos = sf::Vector2f(0.f, 0.f), sf::Vector2f vel = sf::Vector2f(0.f, 0.f), string texturePath = "", float* t = nullptr, sf::RenderWindow* window = nullptr);
    ~Bomb();

    void collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e);
    void update();
    void save();
};