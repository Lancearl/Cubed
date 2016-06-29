#include "stdafx.h"
#include "Character.h"
#include <iostream>

using namespace std;

Player::Player(int hitPoints, int width, int height)
{
	this -> hitPoints = hitPoints;
	// used to return player to max hit points if they restart
	this->maxHitPoints = hitPoints;

	// Health bar
	healthBarHeight = 20.f;
	healthBar = sf::RectangleShape(sf::Vector2f(hitPoints*4, healthBarHeight));
	healthBar.setPosition(5, 5);
	healthBar.setFillColor(sf::Color::Green);

	// Colour overlay
	colourOverlay = sf::RectangleShape(sf::Vector2f(width, height));
	colourOverlay.setPosition(0.f, 0.f);
	colourOverlay.setFillColor(sf::Color(255, 0, 0, 50));

	fovY = 90;
	aspect = 1.0f;
	zNear = 1.0f;
	zFar = 300.0f;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	// define a perspective projection
	glFrustum(-fW, fW, -fH, fH, zNear, zFar); // multiply the set matrix; by a perspective matrix

	// used to ensure that the W and S keys move the player forward and backwards according to
	// where the camera is facing
	lx = 0.0f;
	lz = -1.0f;
	angle = 0.0f;

	// player position
	pos.x = 0.0f;
	pos.z = 15.0f;
	// height of player above ground, 1 seems about right
	pos.y = 1.0f;

	turnSpeed = 0.05; // speed of turning
	movementSpeed = 0.2;

	// gravity * acceleration to progressively increase rate of falling
	gravity = 0.3;
	acceleration = 1.05;


	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// error
		cout << "could not find font" << endl;
	}

	// gameover text
	text = sf::Text("You Died", font);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Black);
	text.setPosition(width/2-(text.getLocalBounds().width/2), height/2-(text.getLocalBounds().height)-50);

	// restart text
	restart = sf::Text("Restart", font);
	restart.setCharacterSize(30);
	restart.setStyle(sf::Text::Bold);
	restart.setColor(sf::Color::Black);
	restart.setPosition(width / 2 - (restart.getLocalBounds().width / 2), height / 2 - (restart.getLocalBounds().height)+ restart.getLocalBounds().height*2);

	// quit text
	quit = sf::Text("Quit", font);
	quit.setCharacterSize(30);
	quit.setStyle(sf::Text::Bold);
	quit.setColor(sf::Color::Black);
	quit.setPosition(width / 2 - (quit.getLocalBounds().width / 2), height / 2 - (quit.getLocalBounds().height) + restart.getLocalBounds().height * 4);
}

Player::~Player()
{
}

void Player::die(sf::RenderWindow &window)
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
	if (mousePos.x > quit.getPosition().x && mousePos.x < quit.getPosition().x+quit.getLocalBounds().width && mousePos.y > quit.getPosition().y && mousePos.y < quit.getPosition().y + quit.getLocalBounds().height+10)
	{
		quit.setColor(sf::Color::White);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			window.close();
		}
	}
	// check if cursor is within restart text bounding box
	else if (mousePos.x > restart.getPosition().x && mousePos.x < restart.getPosition().x + restart.getLocalBounds().width && mousePos.y > restart.getPosition().y && mousePos.y < restart.getPosition().y + restart.getLocalBounds().height + 10)
	{
		restart.setColor(sf::Color::White);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// reset game data
			this->alive = true;
			hitPoints = maxHitPoints;
			pos.x = 0.0f;
			pos.z = 15.0f;
			pos.y = 1.0f;
			gravity = 0.3;
			lx = 0.0f;
			lz = -1.0f;
			angle = 0.0f;
			window.setMouseCursorVisible(false);
		}
	}
	// if cursor isn't in either bounding box, set text colour back to black
	else
	{
		quit.setColor(sf::Color::Black);
		restart.setColor(sf::Color::Black);
	}
}

void Player::checkInput()
{
	sf::Event event;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		pos.x += lx * movementSpeed;
		pos.z += lz * movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		pos.x -= lx * movementSpeed;
		pos.z -= lz * movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		angle -= turnSpeed;
		lx = sin(angle);
		lz = -cos(angle);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		angle += turnSpeed;
		lx = sin(angle);
		lz = -cos(angle);
	}
	// print out player position
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		cout << pos.x << endl;
		cout << pos.y << endl;
		cout << pos.z << endl;
	}
}

void Player::update()
{
	// Update health bar
	healthBar.setSize(sf::Vector2f(hitPoints * 4.f, healthBarHeight));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Check to see if the player is on the platform
	if (pos.z < -30.0f || pos.z > 30.0f || pos.x > 30.0f || pos.x < -30.0f || pos.y < -5)
	{
		pos.y -= gravity;
		if (gravity < 7)
			gravity *= acceleration;
	}
	// Player dies once they reach -1800 on the y axis
	if (pos.y < -1800.0f)
		hitPoints = 0;
	// player is dead
	if (hitPoints < 1)
		alive = false;

	// Update health bar
	healthBar.setSize(sf::Vector2f(hitPoints * 4.f, healthBarHeight));

	// update where the camera/player is looking
	gluLookAt(pos.x, pos.y, pos.z,
		pos.x + lx, pos.y, pos.z + lz,
		0.0f, 1.0f, 0.0f);
}

void Player::drawHealthBar(sf::RenderWindow &window)
{
	window.draw(healthBar);
}

//http://stackoverflow.com/questions/6171092/how-to-make-camera-follow-a-3d-object-in-opengl
//https://www.opengl.org/archives/resources/faq/technical/viewing.htm
