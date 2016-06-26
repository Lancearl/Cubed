#include "Mesh.h"

#pragma once
class Character
{
public:
	Character();
	Character(const char* filename, int hitPoints);
	~Character();
	void draw();
protected:
	Mesh mesh;
	int hitPoints;
};

class Player : public Character 
{
public:
	Player();
	~Player();
	void update(sf::Vector3f &playerPos, sf::Vector3f &playerRotation);
	sf::Vector3f getPlayerPos();
	sf::Vector3f getPlayerRotation();
private:
	sf::Vector3f playerPos;
	sf::Vector3f playerRotation;
};

