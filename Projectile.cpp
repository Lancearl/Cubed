#include "stdafx.h"
#include "Projectile.h"
#include "VectorMath.h"


Projectile::Projectile(char* projectileMesh, sf::Vector2f origin, sf::Vector2f direction)
{
	mesh = Mesh();
	mesh.load(projectileMesh);
	mesh.setheight(PROJECTILE_HEIGHT);
	location = origin;
	velocity = vm::setMagnitude(direction,VELOCITY);
}

void Projectile::move() {
	location += velocity;
	mesh.setLocation(location);
	mesh.draw();
}

Projectile::~Projectile()
{
}
