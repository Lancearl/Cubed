#include "Mesh.h"
#include "Projectile.h"

#pragma once
class Character
{
public:
	Character();
	~Character();
	sf::Vector3f getPos();
	sf::Vector3f pos;
	void takeDamage(int damage);
	bool getAlive();
	bool testCollision(sf::Vector2f object, float BoundSize);
	std::vector<Projectile> projectiles;
protected:
	int hitPoints;
	int maxHitPoints;
	bool alive;
};

class Enemy : public Character 
{
public:
	Enemy();
	Enemy(int hitPoints);
	~Enemy();
	void update(sf::Vector3f &playerPos, sf::Vector3f &playerRotation);
	void draw();
	void shoot(sf::Vector3f playerPos);
protected:
	Mesh mesh;

};
// The players varaiables
class Player : public Character
{
public:
	Player();
	Player(int hitPoints, int width, int height);
	~Player();
	void update(sf::RenderWindow &window);
	void checkInput(sf::RenderWindow &window);
	void drawHud(sf::RenderWindow &window);
	void die(sf::RenderWindow &window);
	void resetGameValues();

private:
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fovY;
	GLdouble aspect;
	GLdouble zNear;
	GLdouble zFar;
	GLdouble fW, fH;

	float lx;
	float ly;
	float lz;

	float angle;
	float angley;
	float gravity;
	float acceleration;

	float healthBarHeight;

	// Movement speed variables
	float turnSpeed; // speed of turning
	float movementSpeed; // movement speed

	sf::RectangleShape healthBar;
	sf::CircleShape crosshair;

	// For turn with mouse
	sf::Vector2f mouseCurrent;
	sf::Vector2f mousePrevious;
};

