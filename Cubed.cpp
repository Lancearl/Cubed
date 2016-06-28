// Dales, Donnell, Harris, Prow
// Cubed - The Game.

#include "stdafx.h"
#include "GL/glew.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Character.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

sf::Time TimePerFrame = sf::seconds(1.f / 60);

float lx = 0.0f, lz = -1.0f;
float angle = 0.0f;
float yPos = -5; // y-axis position

// These are really high at the moment because movement is being handled inside the loop but outside the frames constraint if statement
// It would be a better idea to have a kind of boolean value to toggle for W,A,S,D inside the current key checks, and then
// simple update the actual movement variables if they are true
float turnSpeed = 0.000009f; // speed of turning
float movementSpeed = 0.00003f;

void processEvents(sf::RenderWindow &window, bool &rotate, float &angleX, float &angleY, float &zPos, float &xPos)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		

		// Close window : exit
		if (event.type == sf::Event::Closed)
			window.close();

		// Escape key : exit
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			window.close();

		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::A)) {
			rotate = !rotate;
		}

		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left)) {
			angleX -= 0.1f;
		}

		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right)) {
			angleX += 0.1f;
		}

		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up)) {
			angleY += 0.1f;
		}

		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) {
			angleY -= 0.1f;
		}

		
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::PageUp)){
			//angle += 0.01f;
			//lx = sin(angle);
			//lz = -cos(angle);
		}

		if (event.type == sf::Event::MouseWheelMoved)
		{
			zPos += (event.mouseWheel.delta*0.1f);
		}
	}
}

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Cubed");

	Player player = Player();
	Camera camera = Camera(player);

	// Create a clock for measuring time elapsed
	sf::Clock Clock;

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // nicest perspective correction calculations

													   //prepare OpenGL surface for Hidden Surface Removal (HSR)
	glClearDepth(1.f); // clear the z-buffer/depth buffer completely +1.0f is the furtherest away
	glClearColor(0.3f, 0.3f, 0.3f, 0.f); // set the background colour for when we clear the screen RGBA values in the 0.0 to 1.0 range. This gives us a nice grey background.

	float zPos = -5; // z-axis position
	float xPos = -5; // z-axis position

				 // Setup a perspective projection & Camera position

				 // GL_PROJECTION what we actually see
	glMatrixMode(GL_PROJECTION); // Select the builtin projection matrix
	glLoadIdentity();  // reset the projection matrix by loading the projection identity matrix

	GLdouble fovY = 90;
	GLdouble aspect = 1.0f;
	GLdouble zNear = 1.0f;
	GLdouble zFar = 300.0f;

	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;

	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	// define a perspective projection
	glFrustum(-fW, fW, -fH, fH, zNear, zFar); // multiply the set matrix; by a perspective matrix

	bool rotate = true;
	float angleX = 1;
	float angleY = 1;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// Start game loop
	while (window.isOpen())
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			xPos += lx * movementSpeed;
			zPos += lz * movementSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			angle -= turnSpeed;
			lx = sin(angle);
			lz = -cos(angle);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			xPos -= lx * movementSpeed;
			zPos -= lz * movementSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			angle += turnSpeed;
			lx = sin(angle);
			lz = -cos(angle);
		}

		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents(window, rotate, angleX, angleY, zPos, xPos);

			glEnable(GL_FOG);
			glFogf(GL_FOG_DENSITY, 0.05f);

			//Prepare for drawing
			// Clear color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear z-buffer and set previously selected colour

																// Apply some transformations for the cube
																// The GL_MODELVIEW is used for transforming our model
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			// A and D rotate left and right at the moment
			gluLookAt(xPos, 1.0f, zPos,
				xPos + lx, 1.0f, zPos + lz,
				0.0f, 1.0f, 0.0f);

			// I've commented these out for the moment for testing and because there's no need to update the "player" or enemy cube's position for version 1
			//player.update(sf::Vector3f(xPos, 0.f, zPos), sf::Vector3f(angleX, angleY, 0)); // position the cube model at z-position -5; ie. away from us
			//camera.update(player);

			//Simple ground to give us some frame of reference
			// Draw ground
			glColor3f(0.9f, 0.9f, 0.9f);
			glBegin(GL_QUADS);
			glVertex3f(-120.0f, -5.0f, -100.0f);
			glVertex3f(-120.0f, -5.0f, 100.0f);
			glVertex3f(120.0f, -5.0f, 100.0f);
			glVertex3f(120.0f, -5.0f, -100.0f);
			glEnd();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glColor3f(1, 0, 0);
			player.draw();

			glEnable(GL_DEPTH_TEST);
			window.display();
		}
	}
	return EXIT_SUCCESS;
}