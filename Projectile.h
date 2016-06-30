#pragma once
#include "Mesh.h"

class Projectile
{
public:
	Projectile(char* projectileMesh, sf::Vector2f origin, sf::Vector2f direction);
	~Projectile();
private:
	const int VELOCITY = 20;
	const int PROJECTILE_HEIGHT = 10;
	Mesh mesh;
	sf::Vector2f location;
	sf::Vector2f velocity;
	void move();
};

