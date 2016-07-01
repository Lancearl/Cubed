#pragma once
#include "Mesh.h"

class Projectile
{
public:
	Projectile();
	Projectile(sf::Vector2f origin, sf::Vector2f direction);
	Projectile(const char* projectileMesh, sf::Vector2f origin, sf::Vector2f direction);
	void move();
	sf::Vector2f location;
	float getBounds();
	void setLocation(sf::Vector2f origin, sf::Vector2f direction);

	~Projectile();
private:
	const int VELOCITY = 20;
	const int PROJECTILE_HEIGHT = 1;
	Mesh mesh;
	sf::Vector2f velocity;
};

