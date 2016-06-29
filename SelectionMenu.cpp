#include "stdafx.h"
#include "SelectionMenu.h"


SelectionMenu::SelectionMenu(int aWidth, int aHeight)
{
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// error
		cout << "could not find font" << endl;
	}

	inMainMenu = true;

	this->width = aWidth;
	this->height = aHeight;

	// Colour overlay
	colourOverlay = sf::RectangleShape(sf::Vector2f(width, height));
	colourOverlay.setPosition(0.f, 0.f);

	// gameover text
	text = sf::Text("Cubed", font);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Black);
	text.setPosition(width / 2 - (text.getLocalBounds().width / 2), height / 2 - (text.getLocalBounds().height) - 50);

	// restart text
	restart = sf::Text("Start Game", font);
	restart.setCharacterSize(30);
	restart.setStyle(sf::Text::Bold);
	restart.setColor(sf::Color::Black);
	restart.setPosition(width / 2 - (restart.getLocalBounds().width / 2), height / 2 - (restart.getLocalBounds().height) + restart.getLocalBounds().height * 2);

	// quit text
	quit = sf::Text("Quit Game", font);
	quit.setCharacterSize(30);
	quit.setStyle(sf::Text::Bold);
	quit.setColor(sf::Color::Black);
	quit.setPosition(width / 2 - (quit.getLocalBounds().width / 2), height / 2 - (quit.getLocalBounds().height) + restart.getLocalBounds().height * 4);
	
	colourOverlay.setFillColor(sf::Color(255, 255, 255, 50));
}


SelectionMenu::~SelectionMenu()
{
}

void SelectionMenu::setDoneMainMenu()
{
	text.setString("You Died");
	text.setPosition(width / 2 - (text.getLocalBounds().width / 2), height / 2 - (text.getLocalBounds().height) - 50);
	colourOverlay.setFillColor(sf::Color(255, 0, 0, 50));

	restart.setString("Restart Game");
	restart.setPosition(width / 2 - (restart.getLocalBounds().width / 2), height / 2 - (restart.getLocalBounds().height) + restart.getLocalBounds().height * 2);

	inMainMenu = false;
}

bool SelectionMenu::getInMainMenu()
{
	return inMainMenu;
}

void SelectionMenu::showMenu(sf::RenderWindow &window, Player &player)
{
	window.setMouseCursorVisible(true);
	// Draw all game overtext
	window.draw(colourOverlay);
	window.draw(text);
	window.draw(restart);
	window.draw(quit);

	// get cursor position
	sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	// check if cursor is within quit text bounding box
	if (mousePos.x > quit.getPosition().x && mousePos.x < quit.getPosition().x + quit.getLocalBounds().width && mousePos.y > quit.getPosition().y && mousePos.y < quit.getPosition().y + quit.getLocalBounds().height + 10)
	{
		restart.setColor(sf::Color::Black);

		quit.setColor(sf::Color::White);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			window.close();
		}
	}
	// check if cursor is within restart text bounding box
	else if (mousePos.x > restart.getPosition().x && mousePos.x < restart.getPosition().x + restart.getLocalBounds().width && mousePos.y > restart.getPosition().y && mousePos.y < restart.getPosition().y + restart.getLocalBounds().height + 10)
	{
		quit.setColor(sf::Color::Black);

		restart.setColor(sf::Color::White);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (inMainMenu)
				setDoneMainMenu();

			window.setMouseCursorVisible(false);
			player.resetGameValues();

			restart.setColor(sf::Color::Black);
		}
	}
}
