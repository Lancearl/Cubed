#include "stdafx.h"
#include "Character.h"

Player::Player(int hitPoints)
{
	this -> hitPoints = hitPoints;

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

	lx = 0.0f;
	lz = -1.0f;
	angle = 0.0f;

	xPos = 5;
	zPos = 5;
	yPos = 1;

	turnSpeed = 0.000009f; // speed of turning
	movementSpeed = 0.00003f;
}

Player::~Player()
{
}

void Player::checkInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		xPos += lx * movementSpeed;
		zPos += lz * movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		angle -= turnSpeed;
		lx = sin(angle);
		lz = -cos(angle);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		xPos -= lx * movementSpeed;
		zPos -= lz * movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		angle += turnSpeed;
		lx = sin(angle);
		lz = -cos(angle);
	}
}

void Player::update()
{
	// Update health bar
	healthBar.setSize(sf::Vector2f(hitPoints * 4.f, healthBarHeight));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	pos = sf::Vector3f(xPos, yPos, zPos);

	// A and D rotate left and right at the moment
	gluLookAt(pos.x, pos.y, pos.z,
		xPos + lx, 1.0f, zPos + lz,
		0.0f, 1.0f, 0.0f);
}

void Player::drawHealthBar(sf::RenderWindow &window)
{
	window.draw(healthBar);
}

//http://stackoverflow.com/questions/6171092/how-to-make-camera-follow-a-3d-object-in-opengl
//https://www.opengl.org/archives/resources/faq/technical/viewing.htm
