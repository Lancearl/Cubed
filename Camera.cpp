#include "stdafx.h"
#include "Camera.h"

Camera::Camera(Player target)
{
	this->cameraTarget = target;
	fovY = 90;
	aspect = 1.0f;
	zNear = 1.0f;
	zFar = 300.0f;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	// define a perspective projection
	glFrustum(-fW, fW, -fH, fH, zNear, zFar); // multiply the set matrix; by a perspective matrix
}

Camera::~Camera()
{
}

void Camera::update(Player target)
{
	cameraPos = target.getPlayerPos() + sf::Vector3f(2 * cos(target.getPlayerRotation().x), 0.5, 2 * sin(target.getPlayerRotation().y));
	cameraUp = sf::Vector3f(0.f, 1.f, 0.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//This is the method that looks at the player, you need a glew library to use it
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, 
		target.getPlayerPos().x, target.getPlayerPos().y, target.getPlayerPos().z, 
		cameraUp.x, cameraUp.y, cameraUp.z);
	glTranslatef(target.getPlayerPos().x, target.getPlayerPos().y, target.getPlayerPos().z);
}

//http://stackoverflow.com/questions/6171092/how-to-make-camera-follow-a-3d-object-in-opengl
//https://www.opengl.org/archives/resources/faq/technical/viewing.htm
