#include "stdafx.h"
#include "Character.h"

Character::Character()
{
	mesh.load("Models/cube2.obj");
	hitPoints = 100;
}

Character::Character(const char* filename, int hitPoints)
{
	mesh.load(filename);
	this->hitPoints = hitPoints;

	//mesh.load("Models/dodecahedron.obj");
	//mesh.load("Models/cube.obj");
	//mesh.load("Models/suzanne.obj");
	//mesh.load("Models/f-16.obj");
	//mesh.load("Models/cube.obj");
	//mesh.load("Models/minicooper.obj");
	//mesh.load("Models/tyra.obj");
	//mesh.load("Models/bunny.obj");
}

void Character::draw()
{
	mesh.draw();
}

Character::~Character()
{
}


