#include "stdafx.h"
#include "Character.h"
#include "VectorMath.h"

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

void Enemy::shoot(sf::Vector3f playerPos)
{
	sf::Vector3f direction = pos - playerPos;
	projectiles.push_back(Projectile("Projectile.mesh", vm::flatten(pos), vm::flatten(direction)));
}

void Enemy::draw()
{
	mesh.draw();
}