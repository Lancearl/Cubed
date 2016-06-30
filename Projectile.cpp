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
	//mesh.draw(); //This is causing the exception: Exception thrown at 0x69B9D80E (nvoglv32.dll) in Cubed.exe: 0xC0000005: Access violation reading location 0x00000000" - LD
}

float Projectile::getBounds(){
	return mesh.getWidth();
}

Projectile::~Projectile()
{
}
