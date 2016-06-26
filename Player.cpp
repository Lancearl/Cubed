#include "stdafx.h"
#include "Character.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::update(sf::Vector3f &playerPos, sf::Vector3f &playerRotation)
{
	this->playerPos = playerPos;
	this->playerRotation = playerRotation;

	// update x,y,z position
	glTranslatef(playerPos.x, playerPos.y, playerPos.z); // position the cube model at z-position -5; ie. away from us
	
	// rotate x,y,z by a given angle in degrees
	glRotatef(playerRotation.x * 20, 0.0f, 1.0f, 0.f); // rotate around the x-axis
	glRotatef(playerRotation.y * 20, 1.0f, 0.0f, 0.f); // rotate around the y-axis
}

sf::Vector3f Player::getPlayerPos()
{
	return playerPos;
}

sf::Vector3f Player::getPlayerRotation()
{
	return playerRotation;
}