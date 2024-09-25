#pragma once
#include "stdafx.h"

/* constantes usadas para definir o tamanho mapa do jogo e iterar sobre. */
static const int MAP_DIMENSION_X = 30;
static const int MAP_DIMENSION_Y = 30;

class Map
{
private:
	sf::Vector2i map[MAP_DIMENSION_X][MAP_DIMENSION_Y];
	sf::Vector2i counter;

public:
	Map(string mapPath = "");
	~Map();

	void loadMap(string mapPath);
	int getInfoXMap(int i, int j);
	int getInfoYMap(int i, int j);
	sf::Vector2i getInfoMap(int i, int j);
};