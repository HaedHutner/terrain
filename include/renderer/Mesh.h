#ifndef _MESH_H
#define _MESH_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Mesh {

	GLuint sizeIndices;

	GLuint vao, ebo, vbo, ubo;

	GLuint grassTexture, dirtTexture, rockTexture, snowTexture;

public:

	Mesh();

	Mesh(std::vector<GLuint> &elements, std::vector<glm::ivec2> &vertices);

	void Bind();

	void Draw();

};

#endif