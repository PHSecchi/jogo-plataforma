#pragma once
#include "stdafx.h"
#include <sstream>

class TextInput
{
private:
	sf::Text textInput;
	sf::Font font;
	std::string text;
	bool selected;
	bool hasLimit;
	bool nameRead;
	int limit;
	sf::RenderWindow* windowPtr;

public:
	TextInput();
	TextInput(int sz, sf::Color color, bool isSelected, sf::RenderWindow* window);
	~TextInput();

	void input(int charType);
	void removeLastChar();
	void setSelected(bool status);
	void endReceiving();
	bool isSelected();
	bool nameSent();
	string getString();
	void draw();
	void updatePosition();
	void setColor(sf::Color color);
	void receiveName(sf::Event event);
	void clear();
	void setNameSent(bool status);
};