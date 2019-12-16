#include "..\..\include\renderer\Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<GLuint>& elements, std::vector<glm::ivec2>& vertices)
	: sizeIndices(elements.size())
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::ivec2), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 2, GL_INT, sizeof(glm::ivec2), (void *) 0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), &elements[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ubo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ubo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ubo);
	

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* textureData = stbi_load("./data/texture/ground/Ground_Dirt_005_COLOR.jpg", &width, &height, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(textureData);

	glBindVertexArray(0);
}

void Mesh::Bind()
{
	glEnableVertexAttribArray(0);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ubo);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ubo);
}



void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, sizeIndices, GL_UNSIGNED_INT, NULL);

	glDisableVertexAttribArray(0);
}
