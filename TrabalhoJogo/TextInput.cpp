#include "TextInput.h"

TextInput::TextInput():
	textInput(),
	text(),
	selected(false),
	hasLimit(true),
	nameRead(false),
	limit(15),
	font(),
	windowPtr()
{
}

TextInput::TextInput(int sz, sf::Color color, bool isSelected, sf::RenderWindow* window):
	textInput(),
	text(),
	selected(false),
	hasLimit(true),
	nameRead(false),
	limit(15),
	font(),
	windowPtr()
{
	if (!font.loadFromFile("assets/fonts/Dimitri.ttf"))
	{
		cout << "Unable to load font in \"TextInput.cpp\"" << endl;
		exit(1);
	}

	textInput.setFont(font);
	textInput.setCharacterSize(sz);
	textInput.setFillColor(color);
	textInput.setOrigin(textInput.getLocalBounds().width / 2, textInput.getLocalBounds().height / 2);
	textInput.setPosition(sf::Vector2f(1280.f / 2 + 210.f, 720 / 3.f));
	selected = isSelected;

	if (selected)
		textInput.setString("_");
	else
		textInput.setString("");
}

TextInput::~TextInput()
{
}

void TextInput::input(int charType)
{
	if (charType != 8 && charType != 13 && charType != 27)
	{
		text += static_cast<char>(charType);
	}
	else if (charType == 8)
	{
		if (text.length() > 0)
		{
			removeLastChar();
		}
	}
	textInput.setString(text + "_");
	updatePosition();
}

void TextInput::removeLastChar()
{
	string t = text;
	string new_t = "";

	for (size_t i = 0; i < t.length() - 1; i++)
	{
		new_t += t[i];
	}

	text = "";
	text = new_t;

	textInput.setString(text);
	updatePosition();
}

void TextInput::setSelected(bool status)
{
	if (status && !selected)
	{
		string t = textInput.getString();
		t += "_";
		textInput.setString(t);
	}

	if (status && selected)
	{
		endReceiving();
	}

	selected = status;

	if (!selected)
	{
		string t = text;
		string new_t = "";

		for (size_t i = 0; i < t.length(); i++)
		{
			new_t += t[i];
		}

		textInput.setString(new_t);
	}
}

void TextInput::endReceiving()
{
	setColor(sf::Color(255, 255, 255));

	string t = text;
	string new_t = "";

	for (size_t i = 0; i < t.length(); i++)
	{
		new_t += t[i];
	}

	text = new_t;

	textInput.setString(text);

	text = "";

	nameRead = true;
}

bool TextInput::isSelected()
{
	return selected;
}

bool TextInput::nameSent()
{
	return nameRead;
}

string TextInput::getString()
{
	return textInput.getString();
}

void TextInput::draw()
{
	windowPtr->draw(textInput);
}

void TextInput::updatePosition()
{
	textInput.setOrigin(textInput.getLocalBounds().width / 2, textInput.getLocalBounds().height / 2);
}

void TextInput::setColor(sf::Color color)
{
	textInput.setFillColor(color);
}

void TextInput::receiveName(sf::Event event)
{
	if (selected)
	{
		int charType = event.text.unicode;
		if ((charType >= 96 && charType <= 122) || charType == 8)
		{
			if (hasLimit)
			{
				if (text.length() <= static_cast<size_t>(limit))
				{
					input(charType);
					cout << static_cast<char>(charType) << endl;
				}
				else if (text.length() > static_cast<size_t>(limit) && charType == 8)
				{
					cout << "delteing char..." << endl;
					removeLastChar();
				}
			}
		}
	}
}

void TextInput::clear()
{
	textInput.setString("");
	text = "";
}

void TextInput::setNameSent(bool status)
{
	nameRead = status;
}