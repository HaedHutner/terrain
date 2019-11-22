#include <renderer/TerrainRenderer.h>

TerrainRenderer::TerrainRenderer(std::mutex &m, TerrainWorld &world, Camera &camera, std::atomic<bool> &isWorking)
	: m(m), world(world), camera(camera), isWorking(isWorking)
{
}

void TerrainRenderer::StartRenderer()
{
	GLFWwindow *window;

	// GLFW Error callback
	glfwSetErrorCallback([](int error, const char *desc) { fputs(desc, stderr); });

	if (!glfwInit())
	{
	    exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	window = glfwCreateWindow(camera.GetScreenX(), camera.GetScreenY(), "Terrain", nullptr, nullptr);

	if (!window)
	{
	    glfwTerminate();
	    exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	// Window resize callback
	glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height){
	    glViewport(0, 0, width, height);
	});

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    std::cout << "Failed to initialize OpenGL context" << std::endl;
	    return;
	}

	const GLubyte* vendor = glGetString(GL_VENDOR); // Returns the vendor
	const GLubyte* renderer = glGetString(GL_RENDERER); // Returns a hint to the model

	printf("%s %s OpenGL %d.%d\n", vendor, renderer, GLVersion.major, GLVersion.minor);

	shader = Shader::FromFiles("C:/Users/Miroslav.VSG/Workspace/terrain/data/shader/test-vertex.glsl", "C:/Users/Miroslav.VSG/Workspace/terrain/data/shader/test-fragment.glsl");

	glBindAttribLocation(shader.Id(), 0, "position");

	shader.Link();

	glClearColor(135.0 / 255.0, 206.0 / 255.0, 235.0 / 255.0, 1.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	shader.Use();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m.lock();
		camera.ProcessKeyInput(window);
		std::vector<TerrainChunk> chunks = world.FetchCachedChunksAt({ (int) camera.GetPosition().x, (int) camera.GetPosition().z }, 4);

		for (auto& chunk : chunks) {
			int resolution = 1;
			DrawSingleTerrainChunk(chunk, resolution);
		}

		// printf("Rendered %d cached chunks\n", chunks.size());
		m.unlock();

		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);

		camera.ProcessMouseInput(window, cursorX, cursorY);

	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	isWorking = false;
}

void TerrainRenderer::DrawSingleTerrainChunk(TerrainChunk &chunk, int &resolution)
{
	GenerateChunkMesh(chunk, resolution);
	BindChunkMesh(chunk, resolution);
	DrawChunkMesh(chunk, resolution);
}

void TerrainRenderer::GenerateChunkMesh(TerrainChunk& chunk, int& resolution)
{
	if (cachedMeshes.find(resolution) != cachedMeshes.end()) {
		return;
	}

	int sideSize = (chunk.GetSize().x / resolution) ;
	int verticesSize = (chunk.GetHeights().size() / resolution);

	std::vector<GLuint> elements = std::vector<GLuint>(verticesSize * 6);
	std::vector<glm::ivec2> vertices = std::vector<glm::ivec2>(verticesSize);

	//			  i +---+ i + 1
	//				|\  |
	//				| \ |
	//				|  \|
	// i + sideSize +---+ i + sizeSize + 1
	//
	// 

	int j = 5;
	for (int i = 0; i < verticesSize; i++) {
		int x = i % sideSize;
		int y = i / sideSize;

		vertices[i] = glm::ivec2(x, y);

		if ((x % 63 == 0) || (y % 63 == 0)) continue;

		elements[j - 5] = i;
		elements[j - 4] = i + sideSize;
		elements[j - 3] = i + sideSize + 1;
		elements[j - 2] = i + sideSize + 1;
		elements[j - 1] = i + 1;
		elements[j    ] = i;

		j += 6;	
	}

	Mesh mesh = Mesh(elements, vertices);
	cachedMeshes[resolution] = mesh;
}

void TerrainRenderer::BindChunkMesh(TerrainChunk& chunk, int &resolution)
{
	cachedMeshes[resolution].Bind();

	glBufferData(GL_UNIFORM_BUFFER, chunk.GetHeights().size() * sizeof(float), &chunk.GetHeights()[0], GL_DYNAMIC_DRAW);
	glUniformBlockBinding(shader.Id(), glGetUniformBlockIndex(shader.Id(), "HeightsBlock"), 0);

	shader.SetUniformMat4("projection", camera.GetProjection());
	shader.SetUniformMat4("view", camera.GetView());
	shader.SetUniformMat4("model", glm::translate(
			glm::mat4(1.0), 
			glm::vec3(
				1.0f * (chunk.GetPosition().x * ( CHUNK_WIDTH - 1)), 
				0.0f,
				1.0f * (chunk.GetPosition().y * ( CHUNK_WIDTH - 1)) 
			)
		)
	);
}

void TerrainRenderer::DrawChunkMesh(TerrainChunk& chunk, int &resolution)
{
	cachedMeshes[resolution].Draw();
}

