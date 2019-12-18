#ifndef _TERRAIN_RENDERER_H
#define _TERRAIN_RENDERER_H

#include <atomic>
#include <mutex>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <renderer/Camera.h>
#include <renderer/Shader.h>
#include <renderer/Mesh.h>
#include <renderer/SkyboxRenderer.h>
#include <TerrainWorld.h>

const std::vector<GLuint> MESH_INDICES;

const std::vector<glm::vec2> MESH_VERTICES;

class TerrainRenderer {

	std::atomic<bool> &isWorking;

	Camera &camera;

	TerrainWorld &world;

	std::mutex &m;

	std::unordered_map<int, Mesh> cachedMeshes;

	Shader shader;

	glm::vec3 theSun;

	void DrawSingleTerrainChunk(TerrainChunk &chunk, int &resolution);

	void UpdateViewport(int width, int height);

public:

	TerrainRenderer(std::mutex &m, TerrainWorld& world, Camera& camera, std::atomic<bool>& isWorking);

	void StartRenderer();

};

#endif