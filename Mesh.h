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

	std::vector < GLfloat > vertices;
	std::vector < GLfloat > uvs;
	std::vector < GLfloat > normals;
	std::vector <unsigned int> idx;

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

	void draw();
	bool load(const char* filename);

	///Do not delete:
	//bool load(const char* filename, 
	//	std::vector < sf::Vector3f > & out_vertices,
	//	std::vector < sf::Vector2f > & out_uvs,
	//	std::vector < sf::Vector3f > & out_normals);
};

