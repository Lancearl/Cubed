#include "GL/glew.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#pragma once

class Mesh
{
public:
	Mesh();
	~Mesh();

	std::vector < GLfloat > vertices, uvs, normals;
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

	void draw();
	bool load(const char* filename);
	<< << << < HEAD

		void setLocation(sf::Vector2f location);
	void setLocation(sf::Vector3f location);
	void setheight(float height);

	///Do not delete:
	//bool load(const char* filename, 
	//	std::vector < sf::Vector3f > & out_vertices,
	//	std::vector < sf::Vector2f > & out_uvs,
	//	std::vector < sf::Vector3f > & out_normals);

private:
	int xLoc = 0;
	int zLoc = 0;
	int yLoc = 0;

	int xRot = 0;
	int yRot = 0;
	int zRot = 0;
	== == == =
		>> >> >> > origin / master
};
