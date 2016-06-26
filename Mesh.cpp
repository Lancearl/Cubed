#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "Mesh.h"

Mesh::Mesh()
{
	//std::vector< sf::Vector3f > vertices;
	//std::vector< sf::Vector2f > uvs;
	//std::vector< sf::Vector3f > normals;
	//bool res = load("Models/cube2.obj", vertices, uvs, normals);
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
			for (int i = 0; i < 3; i++)
			{
				GLfloat tmp;
				data >> tmp;
				vertices.push_back(tmp);
			}
		}

		else if (prefix == "vn") // process vertex normals
		{
			for (int i = 0; i < 3; i++)
			{
				GLfloat tmp;
				data >> tmp;
				normals.push_back(tmp);
			}
		}

		else if (prefix == "vt") // process vertex texture
		{
			for (int i = 0; i < 2; i++)
			{
				GLfloat tmp;
				data >> tmp;
				uvs.push_back(tmp);
			}
		}

		else if (prefix == "f") // process face
		{
			for (int i = 0; i < 3; i++)
			{
				std::string face;
				data >> face;

				std::istringstream faceData(face);
				std::string vertex1;

				while (std::getline(faceData, vertex1, '/'))
				{
					std::istringstream vertexData(vertex1);
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
	return true;
}

///Lance's code: a work in progress (do not delete)

//bool Mesh::load(const char* filename, 
//	std::vector < sf::Vector3f > & out_vertices,
//	std::vector < sf::Vector2f > & out_uvs,
//	std::vector < sf::Vector3f > & out_normals)
//{
//	std::ifstream file(filename);
//
//	// For conversion to Vector3f and Vector2f
//	std::vector < GLfloat > temp_vertices;
//	std::vector < GLfloat > temp_uvs;
//	std::vector < GLfloat > temp_normals;
//
//	// To be used in calculating the out values
//	std::vector < sf::Vector3f > temp_vertices1;
//	std::vector < sf::Vector2f > temp_uvs1;
//	std::vector < sf::Vector3f > temp_normals1;
//
//	//std::string materialFile;
//	//std::string materialName;
//
//	std::string line;
//	while (std::getline(file, line))
//	{
//		std::istringstream data(line);
//
//		std::string prefix;
//		data >> prefix;
//
//		if (prefix == "#")
//		{
//			// comment don't do anything
//			continue;
//		}
//		else if (prefix == "mtllib")
//		{
//			// material file not implemented yet
//			//data >> materialFile;
//			//std::cout << materialFile << "\n";
//			continue;
//		}
//		else if (prefix == "usemtl")
//		{
//			// material definition not implemented yet
//			//data >> materialName;
//			//std::cout << materialFile << "\n";
//			continue;
//		}
//		else if (prefix == "o")
//		{
//			// object name ignored
//			continue;
//		}
//		else if (prefix == "s")
//		{
//			// smooth shading ignored
//			continue;
//		}
//
//		else if (prefix == "v") // process vertex
//		{
//			// Go through numbers, store in temporary vector
//			for (int i = 0; i < 3; i++)
//			{
//				GLfloat vertex;
//				data >> vertex;
//				temp_vertices.push_back(vertex);
//			}
//			//convert to vector3f
//			sf::Vector3f vertex(temp_vertices[0], temp_vertices[1], temp_vertices[2]); // x,y,z
//			temp_vertices1.push_back(vertex);
//			temp_vertices.clear(); // clear the vector
//		}
//
//		else if (prefix == "vt") // process vertex texture
//		{
//			for (int i = 0; i < 2; i++)
//			{
//				GLfloat uv;
//				data >> uv;
//				temp_uvs.push_back(uv);
//			}
//			//convert to vector2f
//			sf::Vector2f uv(temp_uvs[0], temp_uvs[1]);
//			temp_uvs1.push_back(uv);
//			temp_uvs.clear();
//		}
//
//		else if (prefix == "vn") // process vertex normals
//		{
//			for (int i = 0; i < 3; i++)
//			{
//				GLfloat normal;
//				data >> normal;
//				temp_normals.push_back(normal);
//			}
//			//convert to vector3f
//			sf::Vector3f normal(temp_normals[0], temp_normals[1], temp_normals[2]);
//			temp_normals1.push_back(normal);
//			temp_normals.clear();
//		}
//
//		else if (prefix == "f") // process face
//		{
//			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//			char v1, v2, v3;
//			unsigned int vInt1, vInt2, vInt3;
//			std::string a = "";
//
//			for (int i = 0; i < 3; i++)
//			{
//				std::string face;
//				data >> face;
//
//				std::istringstream faceData(face);
//				std::string value;
//
//				a.clear();
//
//				while (std::getline(faceData, value))
//				{
//					// Ignore the '/' characters and store the numbers in a string
//					for (auto j = value.begin(); j != value.end(); ++j)
//					{
//						if (*j == '/')
//						{
//							continue;
//						}
//						else
//						{
//							a += *j;
//						}
//					}
//				}
//
//				// Cast chars to unsigned ints and add to temporary arrays
//				// Face: 0 = vertex (v), 1 = vertex texture (vt), 2 = normal (vn)
//				v1 = a[0]; v2 = a[1]; v3 = a[2];
//				std::stringstream strValue1;
//				strValue1 << v1; strValue1 >> vInt1;
//				vertexIndex[i] = vInt1;
//
//				std::stringstream strValue2;
//				strValue2 << v2; strValue2 >> vInt2;
//				uvIndex[i] = vInt2;
//
//				std::stringstream strValue3;
//				strValue3 << v3; strValue3 >> vInt3;
//				normalIndex[i] = vInt3;
//
//				// After gathering the 3 points, add them to the vertice, uv and normal vectors
//				if (i == 2)
//				{
//					vertexIndices.push_back(vertexIndex[0]);
//					vertexIndices.push_back(vertexIndex[1]);
//					vertexIndices.push_back(vertexIndex[2]);
//
//					uvIndices.push_back(uvIndex[0]);
//					uvIndices.push_back(uvIndex[1]);
//					uvIndices.push_back(uvIndex[2]);
//
//					normalIndices.push_back(normalIndex[0]);
//					normalIndices.push_back(normalIndex[1]);
//					normalIndices.push_back(normalIndex[2]);
//				}
//			}
//
//			// For each vertex of each triangle
//			for (unsigned int i = 0; i < vertexIndices.size(); i++) 
//			{
//				unsigned int vertexIndex = vertexIndices[i];
//				sf::Vector3f vertex = temp_vertices1[vertexIndex - 1];
//				out_vertices.push_back(vertex);
//			}
//			
//			for (unsigned int i = 0; i < uvIndices.size(); i++)
//			{
//				unsigned int uvIndex = uvIndices[i];
//				sf::Vector2f uv = temp_uvs1[uvIndex - 1];
//				out_uvs.push_back(uv);
//			}
//
//			for (unsigned int i = 0; i < normalIndices.size(); i++)
//			{
//				unsigned int normalIndex = normalIndices[i];
//				sf::Vector3f normal = temp_normals1[normalIndex - 1];
//				out_normals.push_back(normal);
//			}
//		}
//		else
//		{
//			continue;
//		}
//
//	}
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
//http://nehe.gamedev.net/tutorial/model_loading/16004/
//https://open.gl/textures
//http://stackoverflow.com/questions/33698382/render-triangle-using-modern-opengl-sfml-and-obj-loader

