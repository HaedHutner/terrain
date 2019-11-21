#ifndef _TERRAIN_RENDERER_H
#define _TERRAIN_RENDERER_H

#include <atomic>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <renderer/Camera.h>
#include <renderer/Shader.h>
#include <TerrainWorld.h>

const std::vector<GLuint> MESH_INDICES;

const std::vector<glm::vec2> MESH_VERTICES;

class TerrainRenderer {

	std::atomic<bool> &isWorking;

	std::atomic<Camera> &camera;

	std::atomic<TerrainWorld> &world;

	Shader shader;

	void DrawSingleTerrainChunk(TerrainChunk chunk);

public:

	TerrainRenderer(std::atomic<TerrainWorld> &world, std::atomic<Camera> &camera, std::atomic<bool> &isWorking);

	void StartRenderer();

};

#endif