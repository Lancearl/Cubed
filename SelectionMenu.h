#pragma once
#include "stdafx.h"
#include <iostream>
#include "character.h"

using namespace std;
//Menu Varaiables
class SelectionMenu
{
public:
	SelectionMenu(int width, int height);
	~SelectionMenu();
	void showMenu(sf::RenderWindow &window, Player &player);
	void setDoneMainMenu();
	bool getInMainMenu();

private:
	sf::Font font;

	sf::Text text;
	sf::Text restart;
	sf::Text quit;

	sf::RectangleShape colourOverlay;

	int width;
	int height;

	bool inMainMenu;
};

