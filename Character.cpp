#include "stdafx.h"
#include "Character.h"

Character::Character()
{
	alive = true;
}

Character::~Character()
{
}

void Character::takeDamage(int damage)
{
	hitPoints -= damage;

	if (hitPoints < 1)
		alive = false;
}

sf::Vector3f Character::getPos()
{
	return pos;
}


