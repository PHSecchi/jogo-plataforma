#include "Map.h"

Map::Map(string mapPath) :
	counter(sf::Vector2i(0, 0)),
	map()
{
	loadMap(mapPath);
}

Map::~Map()
{
}

void Map::loadMap(string mapPath)
{
	ifstream ifs(mapPath);

	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			string str;
			ifs >> str;
			char x = str[0], y = str[2];
			map[counter.x][counter.y] = sf::Vector2i(x - '0', y - '0');
			if (ifs.peek() == '\n')
			{
				counter.x = 0;
				counter.y++;
			}
			else
				counter.x++;
		}

		counter.y++;
	}
	else
	{
		cout << "Unable to load the map in \"Map.cpp\": does " << mapPath << " exist?" << endl;
		exit(1);
	}
}

int Map::getInfoXMap(int i, int j) {
	return map[i][j].x;
}

int Map::getInfoYMap(int i, int j) {
	return map[i][j].y;
}

sf::Vector2i Map::getInfoMap(int i, int j)
{
	return map[i][j];
}