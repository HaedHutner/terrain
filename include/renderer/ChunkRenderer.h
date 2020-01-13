#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include <mutex>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <renderer/Camera.h>
#include <renderer/Shader.h>
#include <renderer/Mesh.h>
#include <TerrainWorld.h>

class ChunkRenderer {

	TerrainWorld& world;

	std::mutex& m;

	std::unordered_map<int, Mesh> cachedMeshes;

	Shader shader;

	glm::vec3 theSun;

	float sunDegrees = 0.0f;

	void DrawSingleTerrainChunk(Camera &camera, TerrainChunk& chunk, int& resolution);

public:

	ChunkRenderer(std::mutex &m, TerrainWorld &world);

	void Init(Camera &camera);

	void Draw(Camera &camera);

};

#endif // !CHUNK_RENDERER_H
