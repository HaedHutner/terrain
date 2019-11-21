#include <renderer/TerrainRenderer.h>

TerrainRenderer::TerrainRenderer(std::atomic<TerrainWorld> &world, std::atomic<Camera> &camera, std::atomic<bool> &isWorking)
	: world(world), camera(camera), isWorking(isWorking)
{
}

void TerrainRenderer::StartRenderer()
{
	//for (int x = -9; x < 10; x++) {
	//	for (int y = -9; y < 10; y++) {

	//		std::vector<TerrainChunk> chunks = world->FetchCachedChunksAt({ CHUNK_WIDTH * x, CHUNK_WIDTH * y }, 3);

	//		int howManyChunks = 0;

	//		for (auto& chunk : chunks) {
	//			howManyChunks++;
	//		}

	//		printf("{%3d, %3d} %2d|", x * CHUNK_WIDTH, y * CHUNK_WIDTH, howManyChunks);
	//	}
	//	std::cout << std::endl;
	//}
	const GLfloat SQUARE_VERTICES[] = {
		-1.0f, -1.0f,  -1.0f, // 0
		1.0f, -1.0f,  -1.0f,  // 1
		1.0f,  1.0f,  -1.0f, // 2
		-1.0f,  1.0f,  -1.0f,  // 3
		-1.0f, -1.0f, 1.0f, // 4
		1.0f, -1.0f, 1.0f,  // 5
		1.0f,  1.0f, 1.0f, // 6
		-1.0f,  1.0f, 1.0f   // 7
	};

	const GLuint SQUARE_INDICES[] = {
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};

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

	window = glfwCreateWindow(camera.load().GetScreenX(), camera.load().GetScreenY(), "Terrain", nullptr, nullptr);

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

	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SQUARE_VERTICES), SQUARE_VERTICES, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SQUARE_INDICES), SQUARE_INDICES, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glClearColor(135.0 / 255.0, 206.0 / 255.0, 235.0 / 255.0, 1.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	shader.Use();

	while (!glfwWindowShouldClose(window))
	{
		Camera cameraCopy = camera.load();

		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);
		cameraCopy.ProcessMouseInput(window, cursorX, cursorY);

		cameraCopy.ProcessKeyInput(window);

	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    glEnableVertexAttribArray(0);

	    glBindVertexArray(vao);
	    glBindBuffer(GL_ARRAY_BUFFER, vbo);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

		shader.SetUniformMat4("projection", cameraCopy.GetProjection());
		shader.SetUniformMat4("view", cameraCopy.GetView());
		shader.SetUniformMat4("model", glm::mat4(1.0f));

	    glDrawElements(GL_TRIANGLES, sizeof(SQUARE_INDICES), GL_UNSIGNED_INT, NULL);

	    glDisableVertexAttribArray(0);

	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	isWorking = false;
}

void TerrainRenderer::DrawSingleTerrainChunk(TerrainChunk chunk)
{
	
}
