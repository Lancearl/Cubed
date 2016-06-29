#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
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
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &normals);
	glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, &vertexIndices[0]);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

bool Mesh::load(const char* filename)
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
			// Go through numbers, store in temporary vector
			for (int i = 0; i < 3; i++)
			{
				GLfloat vertex;
				data >> vertex;
				vertices.push_back(vertex);
			}
		}

		else if (prefix == "vt") // process vertex texture
		{
			for (int i = 0; i < 2; i++)
			{
				GLfloat uv;
				data >> uv;
				uvs.push_back(uv);
			}
		}

		else if (prefix == "vn") // process vertex normals
		{
			for (int i = 0; i < 3; i++)
			{
				GLfloat normal;
				data >> normal;
				normals.push_back(normal);
			}
		}

		else if (prefix == "f") // process face
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			char v1, v2, v3;
			unsigned int vInt1, vInt2, vInt3;
			std::string a = "";

			for (int i = 0; i < 3; i++)
			{
				std::string face;
				data >> face;

				std::istringstream faceData(face);
				std::string value;

				a.clear();

				while (std::getline(faceData, value))
				{
					// Ignore the '/' characters and store the numbers in a string
					for (auto j = value.begin(); j != value.end(); ++j)
					{
						if (*j == '/')
						{
							continue;
						}
						else
						{
							a += *j;
						}
					}
				}

				// Cast chars to unsigned ints and add to temporary arrays
				// Face: 0 = vertex (v), 1 = vertex texture (vt), 2 = normal (vn)
				v1 = a[0]; v2 = a[1]; v3 = a[2];
				std::stringstream strValue1;
				strValue1 << v1; strValue1 >> vInt1;
				vertexIndex[i] = vInt1;

				std::stringstream strValue2;
				strValue2 << v2; strValue2 >> vInt2;
				uvIndex[i] = vInt2;

				std::stringstream strValue3;
				strValue3 << v3; strValue3 >> vInt3;
				normalIndex[i] = vInt3;

				// After gathering the 3 points, add them to the vertice, uv and normal indices vectors
				if (i == 2)
				{
					vertexIndices.push_back(vertexIndex[0] - 1);
					vertexIndices.push_back(vertexIndex[1] - 1);
					vertexIndices.push_back(vertexIndex[2] - 1);

					uvIndices.push_back(uvIndex[0]);
					uvIndices.push_back(uvIndex[1]);
					uvIndices.push_back(uvIndex[2]);

					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
				}
			}
		}
		else
		{
			continue;
		}
	}
	return true;
}
