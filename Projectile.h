#pragma once
#include "Mesh.h"

class Projectile
{
public:
	Projectile(char* projectileMesh, sf::Vector2f origin, sf::Vector2f direction);
	void move();
	sf::Vector2f location;
	float getBounds();

	~Projectile();
private:
	const int VELOCITY = 20;
	const int PROJECTILE_HEIGHT = 10;
	Mesh mesh;
	sf::Vector2f velocity;
};

