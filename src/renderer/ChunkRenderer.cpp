#include "..\..\include\renderer\ChunkRenderer.h"

ChunkRenderer::ChunkRenderer(std::mutex& m, TerrainWorld& world) : m(m), world(world), theSun({0.0f, 0.8f, 0.0f})
{
}

void ChunkRenderer::Init(Camera& camera)
{
	shader = Shader::FromFiles("./data/shader/terrain-vertex.glsl", "./data/shader/terrain-fragment.glsl");

	glBindAttribLocation(shader.Id(), 0, "position");

	shader.Link();
}

void ChunkRenderer::Draw(Camera& camera)
{
	int resolution = 1;

	m.lock();
	std::vector<TerrainChunk> chunks = world.FetchCachedChunksAt({ (int)camera.GetPosition().x, (int)camera.GetPosition().z }, 5);
	m.unlock();

	shader.Use();

	shader.SetUniformInt("grassTexture", 0);
	shader.SetUniformInt("rockTexture", 1);
	shader.SetUniformInt("dirtTexture", 2);
	shader.SetUniformInt("snowTexture", 3);

	shader.SetUniformVec3("cameraPosition", camera.GetPosition());
	shader.SetUniformVec3("theSun", theSun);
	shader.SetUniformInt("resolution", 1);
	shader.SetUniformMat4("projection", camera.GetProjection());
	shader.SetUniformMat4("view", camera.GetView());

	for (auto& chunk : chunks) {
		DrawSingleTerrainChunk(camera, chunk, resolution);
	}

	theSun = glm::rotateX(theSun, sunDegrees);
}

void ChunkRenderer::DrawSingleTerrainChunk(Camera &camera, TerrainChunk& chunk, int& resolution)
{
	if (cachedMeshes.find(resolution) == cachedMeshes.end()) {
		int sideSize = ((chunk.GetSize().x - 1) / resolution);
		int verticesSize = sideSize * sideSize;

		std::vector<GLuint> elements = std::vector<GLuint>(verticesSize * 6);
		std::vector<glm::ivec2> vertices = std::vector<glm::ivec2>(verticesSize);
		// std::vector<glm::ivec2> uvs = std::vector<glm::ivec2>(verticesSize);

		//            i - 1 +---+ i 
		//			    	|\  |
		//		    		| \ |
		//	     			|  \|
		// i - sideSize - 1 +---+ i - sideSize
		int j = 5;
		for (int i = 0; i < verticesSize; i++) {
			int x = i % sideSize;
			int y = i / sideSize;

			vertices[i] = glm::ivec2(x, y);
			// uvs[i] = vertices[i];

			if (x == 0 || y == 0) continue;

			elements[j] = i - 1;
			elements[j - 1] = i - sideSize - 1;
			elements[j - 2] = i - sideSize;
			elements[j - 3] = i - sideSize;
			elements[j - 4] = i;
			elements[j - 5] = i - 1;

			j += 6;
		}

		Mesh mesh = Mesh(elements, vertices);
		cachedMeshes[resolution] = mesh;
	}

	cachedMeshes[resolution].Bind();

	glBufferData(GL_SHADER_STORAGE_BUFFER, chunk.GetHeights().size() * sizeof(glm::vec4), &chunk.GetHeights()[0], GL_DYNAMIC_DRAW);
	// glBufferSubData(GL_SHADER_STORAGE_BUFFER, chunk.GetHeights().size() * sizeof(glm::vec4), uvs.size() * sizeof(glm::ivec2), &uvs[0]);

	shader.SetUniformMat4("model", glm::translate(
		glm::mat4(1.0),
		glm::vec3(
			1.0f * (chunk.GetPosition().x) * (chunk.GetSize().x - 2),
			0.0f,
			1.0f * (chunk.GetPosition().y) * (chunk.GetSize().y - 2)
		)
	)
	);

	cachedMeshes[resolution].Draw();
}