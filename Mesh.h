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
};
