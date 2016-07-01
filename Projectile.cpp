#include "stdafx.h"
#include "Projectile.h"
#include "VectorMath.h"

Projectile::Projectile()
{
	mesh.load("Models/cube3.obj");
	mesh.setHeight(PROJECTILE_HEIGHT);
}

Projectile::Projectile(sf::Vector2f origin, sf::Vector2f direction)
{
	mesh.load("Models/cube3.obj");
	mesh.setHeight(PROJECTILE_HEIGHT);
	location = origin;
	velocity = vm::setMagnitude(direction,VELOCITY);
}

Projectile::Projectile(const char* projectileMesh, sf::Vector2f origin, sf::Vector2f direction)
{
	mesh.load(projectileMesh);
	mesh.setHeight(PROJECTILE_HEIGHT);
	location = origin;
	velocity = vm::setMagnitude(direction,VELOCITY);
}

void Projectile::setLocation(sf::Vector2f origin, sf::Vector2f direction)
{
	location = origin;
	velocity = vm::setMagnitude(direction, VELOCITY);
}

void Projectile::move() 
{
	location += velocity;
	mesh.setLocation(location);
	mesh.draw(); 
}

float Projectile::getBounds(){
	return mesh.getWidth();
}

Projectile::~Projectile()
{
}
