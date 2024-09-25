#pragma once
#include "stdafx.h"
#include "Menu.h"
#include "TextInput.h"
#include <fstream>
#include <map>

#define RANKING_MAX_ITEMS 3
#define RANKING_MAX_PLAYERS 5

class MainMenu;

class Ranking :
    public Menu
{
private:
    sf::Text menuOptions[RANKING_MAX_ITEMS];
    sf::Text leader[RANKING_MAX_PLAYERS];
    sf::Text positions[RANKING_MAX_PLAYERS];
    sf::Text scores[RANKING_MAX_PLAYERS];
    vector<pair<string, float>> rankingList;
    TextInput textInput;
    MainMenu* mainMenuPtr;
    Player* playerPtr;
    bool nameSet;

public:
    Ranking(StateManager* stateManager = nullptr, GraphicsManager* graphicsManager = nullptr, string bgPath = "", sf::RenderWindow* window = nullptr);
    ~Ranking();

    void draw();
    void moveUp();
    void moveDown();
    void selectOption();
    void update(sf::Event event);

    void setPlayer(Player* player);
    void restartPlayerScore();

    void initLeaderboard();
    void initRanking();
    void initNames();
    void initPositions();
    void initScores();
    
    void setMainMenu(MainMenu* mainMenu);
    void setNameStatus(bool status);
    
    void addScore(string name, float score);
    void updateRanking();
    void sortRanking(vector<pair<string, float>> &vector);
    void saveScore();
    void loadScore();
    void restartInfo();
};