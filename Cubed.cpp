// Dales, Donnell, Harris, Prow
// Cubed - The Game.

#include "stdafx.h"
#include "GL/glew.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Character.h"
#include "SelectionMenu.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

sf::Time TimePerFrame = sf::seconds(1.f / 60);

void processEvents(sf::RenderWindow &window)
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
	}
}

int main()
{
	// Create the main window
	sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
	sf::RenderWindow window(desktop, "Cubed", sf::Style::None);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);

	// Create a clock for measuring time elapsed
	sf::Clock Clock;

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // nicest perspective correction calculations

	//prepare OpenGL surface for Hidden Surface Removal (HSR)
	glClearDepth(1.f); // clear the z-buffer/depth buffer completely +1.0f is the furtherest away
	glClearColor(0.f, 0.f, 0.f, 0.f); // set the background colour for when we clear the screen RGBA values in the 0.0 to 1.0 range. This gives us a nice grey background.


	// Setup a perspective projection & Camera position
	// GL_PROJECTION what we actually see
	glMatrixMode(GL_PROJECTION); // Select the builtin projection matrix
	glLoadIdentity();  // reset the projection matrix by loading the projection identity matrix

	// Instantiate player and enemy and give each 100 health
	Enemy enemy = Enemy(100);
	Player player = Player(100,window.getSize().x, window.getSize().y);

	// object for display menu
	SelectionMenu menu = SelectionMenu(window.getSize().x, window.getSize().y);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// Start game loop
	while (window.isOpen())
	{
		
		// Check for player input and move player camera accordingly
		

		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > TimePerFrame)
		{
			// Temporary to test damage taking
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			{
				player.takeDamage(5);
			}

			timeSinceLastUpdate -= TimePerFrame;
			processEvents(window);

			// Enable fog
			glEnable(GL_FOG);
			glFogf(GL_FOG_DENSITY, 0.05f);

			//Prepare for drawing
			// Clear color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear z-buffer and set previously selected colour
			
																// Perform all 2D drawing of SFML shapes and text here. SFML uses openGL to draw these things, which can mess
					
															// with the rendering if not between push and pop states
			player.update(window);

			//Simple ground to give us some frame of reference
			glColor3f(0.9f, 0.9f, 0.9f);
			glBegin(GL_QUADS);
			glVertex3f(-30.0f, -5.0f, -30.0f);
			glVertex3f(-30.0f, -5.0f, 30.0f);
			glVertex3f(30.0f, -5.0f, 30.0f);
			glVertex3f(30.0f, -5.0f, -30.0f);
			glEnd();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glColor3f(1, 0, 0);
			enemy.draw();

			window.pushGLStates();
			if (menu.getInMainMenu())
			{
				menu.showMenu(window,player);
			}
			else
			{
				for each(Projectile projectile in enemy.projectiles) {
					player.testCollision(projectile.location, projectile.getBounds);
				}
				if (player.getAlive())
				{
					player.drawHud(window);
					player.checkInput();
				}
				else
				{
					menu.showMenu(window, player);
				}
				
			}
			window.popGLStates();

			glEnable(GL_DEPTH_TEST);
			window.display();
		}
	}
	return EXIT_SUCCESS;
}