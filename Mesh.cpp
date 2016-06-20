#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glDrawElements(GL_TRIANGLES, idx.size(), GL_UNSIGNED_INT, &idx[0]);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Mesh::load(const char* filename)
{
	std::ifstream file(filename);

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream data(line);

		std::string prefix;
		data >> prefix;

		if (prefix == "#")
		{
			// comment don't do anything
			continue;
		}
		else if (prefix == "mtllib")
		{
			// material file not implemented yet
			continue;
		}
		else if (prefix == "usemtl")
		{
			// material definition not implemented yet
			continue;
		}
		else if (prefix == "o")
		{
			// object name ignored
			continue;
		}
		else if (prefix == "s")
		{
			// smooth shading ignored
			continue;
		}
		else if (prefix == "v") // process vertex
		{
			for (int i = 0; i < 3; i++)
			{
				GLfloat tmp;
				data >> tmp;
				vertices.push_back(tmp);
			}
		}
		else if (prefix == "f") // process face
		{
			for (int i = 0; i < 3; i++)
			{
				std::string face;
				data >> face;

				std::istringstream faceData(face);
				std::string vertex;

				while (std::getline(faceData, vertex, '/'))
				{
					std::istringstream vertexData(vertex);

					unsigned int tmp;
					vertexData >> tmp;
					idx.push_back(tmp - 1);
					break; //TODO implement texture co-ordinates and normals
				}
			}
		}
		else
		{
			// ignore anything else
			continue;
		}
	}
}


