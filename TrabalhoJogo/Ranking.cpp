#include "Ranking.h"
#include "MainMenu.h"

bool cmp(pair<string, float> &a, pair<string, float> &b)
{
	return a.second > b.second;
}

Ranking::Ranking(StateManager* stateManager, GraphicsManager* graphicsManager, string bgPath, sf::RenderWindow* window):
	Menu(stateManager, graphicsManager, bgPath, window),
	menuOptions(),
	rankingList(),
	leader(),
	positions(),
	scores(),
	nameSet(false)
{
	mainMenuPtr = nullptr;
	playerPtr = nullptr;
	loadScore();
	initLeaderboard();
	initRanking();
}

Ranking::~Ranking()
{
	playerPtr = nullptr;
	saveScore();
}

void Ranking::initLeaderboard()
{
	if (!titleFont.loadFromFile("assets/fonts/Dimitri.ttf"))
	{
		cout << "Unable to load font in \"Ranking.cpp\"" << endl;
		exit(1);
	}

	if (!itemFont.loadFromFile("assets/fonts/Dimitri.ttf"))
	{
		cout << "Unable to load font in \"Ranking.cpp\"" << endl;
		exit(1);
	}

	sf::FloatRect textRect;

	menuOptions[0].setFont(titleFont);
	menuOptions[0].setCharacterSize(104);
	menuOptions[0].setFillColor(sf::Color::White);
	menuOptions[0].setString("Ranking");
	textRect = menuOptions[0].getLocalBounds();
	menuOptions[0].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[0].setPosition(sf::Vector2f(WIDTH / 3.f * 2, HEIGHT / 8 * 4));

	menuOptions[1].setFont(itemFont);
	menuOptions[1].setCharacterSize(54);
	menuOptions[1].setFillColor(sf::Color::Black);
	menuOptions[1].setString("Save score");
	textRect = menuOptions[1].getLocalBounds();
	menuOptions[1].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[1].setPosition(sf::Vector2f(WIDTH / 3.f * 2, HEIGHT / 8 * 5));

	menuOptions[2].setFont(itemFont);
	menuOptions[2].setCharacterSize(54);
	menuOptions[2].setFillColor(sf::Color::Black);
	menuOptions[2].setString("Back to main menu");
	textRect = menuOptions[2].getLocalBounds();
	menuOptions[2].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	menuOptions[2].setPosition(sf::Vector2f(WIDTH / 3.f * 2, HEIGHT / 8 * 6));
}

void Ranking::initRanking()
{
	initNames();
	initPositions();
	initScores();
	updateRanking();
}

void Ranking::initNames()
{
	sf::FloatRect textRect;

	for (int i = 0; i < RANKING_MAX_PLAYERS; i++)
	{
		leader[i].setFont(itemFont);
		leader[i].setCharacterSize(27);
		leader[i].setFillColor(sf::Color::Green);
		leader[i].setString(rankingList[i].first);
		textRect = leader[i].getLocalBounds();
		leader[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		leader[i].setPosition(sf::Vector2f(WIDTH / 3.f * 1, HEIGHT / 8 * (3 + i)) + sf::Vector2f(-50.f, -50.f));
	}
}

void Ranking::initPositions()
{
	sf::FloatRect textRect;

	for (int i = 0; i < RANKING_MAX_PLAYERS; i++)
	{
		int j = i + 1;
		positions[i].setFont(itemFont);
		positions[i].setCharacterSize(27);
		positions[i].setFillColor(sf::Color::Magenta);
		positions[i].setString(to_string(j));
		textRect = positions[i].getLocalBounds();
		positions[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		positions[i].setPosition(leader[i].getPosition() + sf::Vector2f(-50.f, 0.f));
	}
}

void Ranking::initScores()
{
	sf::FloatRect textRect;

	for (int i = 0; i < RANKING_MAX_PLAYERS; i++)
	{
		float j = rankingList[i].second;
		scores[i].setFont(itemFont);
		scores[i].setCharacterSize(27);
		scores[i].setFillColor(sf::Color::Cyan);
		scores[i].setString(to_string(static_cast<int>(j)));
		textRect = scores[i].getLocalBounds();
		scores[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		scores[i].setPosition(leader[i].getPosition() + sf::Vector2f(200.f, 0.f));
	}
}

void Ranking::moveUp()
{
	/* there is the title at 0 index . */
	if (selectedOption - 1 >= 1)
	{
		menuOptions[selectedOption].setFillColor(sf::Color::Black);
		selectedOption--;
		menuOptions[selectedOption].setFillColor(sf::Color::Red);
	}
}

void Ranking::moveDown()
{
	if (selectedOption + 1 < RANKING_MAX_ITEMS)
	{
		menuOptions[selectedOption].setFillColor(sf::Color::Black);
		selectedOption++;
		menuOptions[selectedOption].setFillColor(sf::Color::Red);
	}
}

void Ranking::draw()
{
	int i;

	windowPtr->draw(background);

	for (i = 0; i < RANKING_MAX_ITEMS; i++)
		windowPtr->draw(menuOptions[i]);

	for (i = 0; i < RANKING_MAX_PLAYERS; i++)
		windowPtr->draw(leader[i]);

	for (i = 0; i < RANKING_MAX_PLAYERS; i++)
		windowPtr->draw(positions[i]);

	for (i = 0; i < RANKING_MAX_PLAYERS; i++)
		windowPtr->draw(scores[i]);
}

void Ranking::selectOption()
{
	if (selectedOption == 1)
	{
		graphicsManagerPtr->setMenu(mainMenuPtr);
		restartInfo();
		restartPlayerScore();
	}
}

void Ranking::update(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			moveUp();
			break;

		case sf::Keyboard::Down:
			moveDown();
			break;

		case sf::Keyboard::Return:
			selectOption();
			break;
		}
	}
}

void Ranking::setMainMenu(MainMenu* mainMenu)
{
	if (mainMenu != nullptr)
		mainMenuPtr = mainMenu;
	else
	{
		cout << "Unable to set mainMenu in \"Ranking.cpp\"" << endl;
		exit(1);
	}
}

void Ranking::setNameStatus(bool status)
{
	nameSet = status;
}

void Ranking::setPlayer(Player* player)
{
	playerPtr = player;
}

void Ranking::addScore(string name, float score)
{
	rankingList.push_back(pair<string, float>(name, score));

	updateRanking();
}

void Ranking::updateRanking()
{
	sortRanking(rankingList);

	for (int i = 0; i < 5; i++)
	{
		leader[i].setString(rankingList[i].first);
		scores[i].setString(to_string(static_cast<int>(rankingList[i].second)));
	}
}

void Ranking::sortRanking(vector<pair<string, float>> &vector)
{
	sort(vector.begin(), vector.end(), cmp);
}

void Ranking::saveScore()
{
	/* file open for writing */
	ofstream ofs("saves/Ranking.txt", ios::out);

	if (ofs.is_open())
	{
		for (size_t i = 0; i < rankingList.size(); i++)
			ofs << rankingList[i].first << ' ' << rankingList[i].second << endl;

		ofs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Ranking.txt\" in \"Ranking.cpp\"" << endl;
		exit(1);
	}
}

void Ranking::loadScore()
{
	/* opens file for reading */
	ifstream ifs("saves/Ranking.txt", ios::in);

	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			float score;
			string playerName;

			ifs >> playerName >> score;

			if (playerName != "")
			{
				pair<string, float> pair(playerName, score);
				rankingList.push_back(pair);
			}
		}

		ifs.close();
	}
	else
	{
		cout << "loadScore() - Unable to open \"saves/Ranking.txt\" in \"Ranking.cpp\"" << endl;
		exit(1);
	}
}

void Ranking::restartInfo()
{
	nameSet = false;
}

void Ranking::restartPlayerScore()
{
	playerPtr->resetScore();
	playerPtr = nullptr;
}