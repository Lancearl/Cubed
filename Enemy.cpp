#include "stdafx.h"
#include "Character.h"

Enemy::Enemy(int hitPoints)
{
	mesh.load("Models/cube2.obj");
	this->hitPoints = hitPoints;
}

Enemy::~Enemy()
{
}

void Enemy::update(sf::Vector3f &playerPos, sf::Vector3f &playerRotation)
{

}

void Enemy::draw()
{
	mesh.draw();
}