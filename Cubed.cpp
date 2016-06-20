// Dales, Donnell, Harris, Prow
// Cubed - The Game.

#include "stdafx.h"

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

sf::Time TimePerFrame = sf::seconds(1.f / 60);

void processEvents(sf::RenderWindow &window, bool &rotate, float &angleX, float &angleY, float &zPos)
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

	Mesh mesh = Mesh();
	//mesh.load("Models/dodecahedron.obj");
	//mesh.load("Models/cube.obj");
	mesh.load("Models/suzanne.obj");
	//mesh.load("Models/f-16.obj");
	//mesh.load("Models/cube.obj");
	//mesh.load("Models/minicooper.obj");
	//mesh.load("Models/tyra.obj");
	//mesh.load("Models/bunny.obj");

	// Create a clock for measuring time elapsed
	sf::Clock Clock;

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // nicest perspective correction calculations

													   //prepare OpenGL surface for HSR
	glClearDepth(1.f); // clear the z-buffer/depth buffer completely +1.0f is the furtherest away
	glClearColor(0.3f, 0.3f, 0.3f, 0.f); // set the background colour for when we clear the screen RGBA values in the 0.0 to 1.0 range. This gives us a nice grey background.

	float zPos = 0; // z-axis position

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
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents(window, rotate, angleX, angleY, zPos);			// Process events

			//Prepare for drawing
			// Clear color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear z-buffer and set previously selected colour

																// Apply some transformations for the cube
																// The GL_MODELVIEW is used for transforming our model
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity(); // reset

			glTranslatef(0.f, 0.f, zPos); // position the cube model at z-position -200; ie. away from us

			// rotate x,y,z by a given angle in degrees
			glRotatef(angleX * 20, 0.0f, 1.0f, 0.f); // rotate around the y-axis
			glRotatef(angleY * 20, 1.0f, 0.0f, 0.f); // rotate around the y-axis

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glColor3f(1, 0, 0);
			mesh.draw();

			glEnable(GL_DEPTH_TEST);
			window.display();
		}
	}
	return EXIT_SUCCESS;
}