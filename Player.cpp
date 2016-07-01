#include "stdafx.h"
#include "Character.h"
#include "VectorMath.h"
#include <iostream>

using namespace std;

Player::Player()
{
	// used to return player to max hit points if they restart
	this->maxHitPoints = 100;

	// set intial game values
	resetGameValues();
	// acceleration to progressively increase rate of falling
	acceleration = 1.05;

	// Health bar
	healthBarHeight = 20.f;
	healthBar = sf::RectangleShape(sf::Vector2f(hitPoints * 4, healthBarHeight));
	healthBar.setPosition(5, 5);
	healthBar.setFillColor(sf::Color::Green);

	fovY = 90;
	aspect = 1.0f;
	zNear = 1.0f;
	zFar = 300.0f;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	// define a perspective projection
	glFrustum(-fW, fW, -fH, fH, zNear, zFar); // multiply the set matrix; by a perspective matrix


	turnSpeed = 0.04; // speed of turning
	movementSpeed = 0.15;

	// crosshair
	crosshair = sf::CircleShape(2.f);
	crosshair.setPosition(1920 / 2 - (crosshair.getLocalBounds().width / 2), 1080 / 2 - (crosshair.getLocalBounds().height / 2));
	crosshair.setFillColor(sf::Color::White);
}

Player::Player(int hitPoints, int width, int height)
{
	// used to return player to max hit points if they restart
	this->maxHitPoints = hitPoints;

	// set intial game values
	resetGameValues();
	// acceleration to progressively increase rate of falling
	acceleration = 1.05;

	// Health bar
	healthBarHeight = 20.f;
	healthBar = sf::RectangleShape(sf::Vector2f(hitPoints*4, healthBarHeight));
	healthBar.setPosition(5, 5);
	healthBar.setFillColor(sf::Color::Green);

	fovY = 90;
	aspect = 1.0f;
	zNear = 1.0f;
	zFar = 300.0f;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	// define a perspective projection
	glFrustum(-fW, fW, -fH, fH, zNear, zFar); // multiply the set matrix; by a perspective matrix


	turnSpeed = 0.04; // speed of turning
	movementSpeed = 0.15;


	// crosshair
	crosshair = sf::CircleShape(2.f);
	crosshair.setPosition(width / 2 - (crosshair.getLocalBounds().width / 2), height / 2 - (crosshair.getLocalBounds().height / 2));
	crosshair.setFillColor(sf::Color::White);
}

Player::~Player()
{
}

void Player::resetGameValues()
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
	ly = 0.0f;
	angle = 0.0f;
	angley = 0.0f;
}
//Checks for user input via Left,Right,UP,Down. 
void Player::checkInput(sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		pos.x += sin(angle) * movementSpeed;
		pos.z += -cos(angle) * movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		pos.x -= sin(angle) * movementSpeed;
		pos.z -= -cos(angle) * movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		pos.x -= sin(angle + 89.537) * movementSpeed;
		pos.z -= -cos(angle + 89.537) * movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		pos.x -= sin(angle - 89.537) * movementSpeed;
		pos.z -= -cos(angle - 89.537) * movementSpeed;
	}
	// print out player position
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		cout << pos.x << endl;
		cout << pos.y << endl;
		cout << pos.z << endl;
	}
	//right
	if (mouseCurrent.x > mousePrevious.x)
	{
		angle += turnSpeed;
	}
	// left
	if (mouseCurrent.x < mousePrevious.x)
	{
		angle -= turnSpeed;
	}
	/**
	// down
	if (mouseCurrent.y > mousePrevious.y)
	{
	if(angley < 10)
	angley += turnSpeed;
	ly = -sin(angley);
	}
	// up
	if (mouseCurrent.y < mousePrevious.y )
	{
	if (angley > -10)
	angley += turnSpeed;
	ly = sin(angley);
	}*/

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			//Left as switch event incase we add more functionality, eg a right mouse click
			switch (event.key.code)
			{
			case (sf::Mouse::Button::Left) : //Shoot event
				projectiles.push_back(Projectile(vm::flatten(pos), sf::Vector2f(sin(angle) * movementSpeed, -cos(angle) * movementSpeed)));
				break;
			}
		}

		// Close window : exit
		if (event.type == sf::Event::Closed)
			window.close();

		// Escape key : exit
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			window.close();
	}
}


bool Character::testCollision(sf::Vector2f object, float objectBounds) {
	sf::Vector2f distance = object - vm::flatten(pos);
	if (abs(vm::magnitude(distance)) < objectBounds) {
		return true;
	}
	return false;
}
//Updates the mouse postion within the game world.
void Player::update(sf::RenderWindow &window)
{
	mousePrevious = mouseCurrent;
	mouseCurrent = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	if ((mouseCurrent.x > window.getSize().x - 10.f || mouseCurrent.x < 10.f || mouseCurrent.y > window.getSize().y - 10.f || mouseCurrent.y < 10.f) && alive)
	{
		sf::Mouse::setPosition(sf::Vector2i(window.getSize().x/2,window.getSize().y/2));
		mousePrevious = mouseCurrent;

		if (mouseCurrent.x < mousePrevious.x)
			mousePrevious.x = -55;
		else
			mousePrevious.x = 55;
			
	}

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
	gluLookAt(pos.x, pos.y, pos.z, // eye location
		pos.x + sin(angle), pos.y + ly, pos.z + -cos(angle), // angle camera is looking at
		0.0f, 1.0f, 0.0f); // up direction
}
//Draws the player connected visuals such as health and the crosshair.
void Player::drawHud(sf::RenderWindow &window)
{
	window.draw(healthBar);
	window.draw(crosshair);
}

//http://stackoverflow.com/questions/6171092/how-to-make-camera-follow-a-3d-object-in-opengl
//https://www.opengl.org/archives/resources/faq/technical/viewing.htm
