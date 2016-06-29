#include "Mesh.h"

#pragma once
class Character
{
public:
	Character();
	~Character();
	sf::Vector3f getPos();
	sf::Vector3f pos;
	void takeDamage(int damage);
protected:
	int hitPoints;
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
protected:
	Mesh mesh;
};

class Player : public Character
{
public:
	Player();
	Player(int hitPoints);
	~Player();
	void update();
	void checkInput();
	void drawHealthBar(sf::RenderWindow &window);

private:
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fovY;
	GLdouble aspect;
	GLdouble zNear;
	GLdouble zFar;
	GLdouble fW, fH;

	float zPos; // z-axis position
	float xPos; // z-axis position
	float lx;
	float lz;
	float angle;
	float yPos;

	float healthBarHeight;

	// Movement speed variables
	float turnSpeed; // speed of turning
	float movementSpeed; // movement speed

	sf::RectangleShape healthBar;
};

