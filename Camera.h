#include "Character.h"

#pragma once

class Camera
{
public:
	Camera(Player target);
	~Camera();
	void update(Player target);

private:
	const GLdouble pi = 3.1415926535897932384626433832795;
	sf::Vector3f cameraPos;
	Player cameraTarget;
	sf::Vector3f cameraUp;
	GLdouble fovY;
	GLdouble aspect;
	GLdouble zNear;
	GLdouble zFar;
	GLdouble fW, fH;
};