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
//Enemy projectile mesh. displays what the enemy is firing.
void Enemy::shoot(sf::Vector3f playerPos)
{
	sf::Vector3f direction = pos - playerPos;
	projectiles.push_back(Projectile("projectile.mesh", vm::flatten(pos), vm::flatten(direction)));
	//where is the above mesh located? their is no projectile mesh that i can find.
}

void Enemy::draw()
{
	mesh.draw();
}