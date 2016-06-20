#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <fstream>
#include <string>
#include <sstream>

#pragma once

class Mesh
{
public:
	Mesh();
	~Mesh();
	void draw();
	void load(const char* filename);

private:
	std::vector <GLfloat> vertices;
	std::vector <unsigned int> idx;
};

