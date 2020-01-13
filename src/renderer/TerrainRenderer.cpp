#include <renderer/TerrainRenderer.h>

TerrainRenderer::TerrainRenderer(std::mutex &m, TerrainWorld &world, Camera &camera, std::atomic<bool> &isWorking)
	: m(m), world(world), camera(camera), isWorking(isWorking), skyboxRenderer(), chunkRenderer(m, world), guiRenderer()
{
}

void TerrainRenderer::UpdateViewport(int width, int height) {
	glViewport(0, 0, width, height);
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

	GLint maxSizeTBO, maxSizeUBO, maxSizeSSBO;
	glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE, &maxSizeTBO);
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &maxSizeUBO);
	glGetIntegerv(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &maxSizeSSBO);

	printf("%s %s OpenGL %d.%d\n", vendor, renderer, GLVersion.major, GLVersion.minor);
	printf("Max TBO size in bytes: %d\n", maxSizeTBO);
	printf("Max UBO size in bytes: %d\n", maxSizeUBO);
	printf("Max SSBO size in bytes: %d\n", maxSizeSSBO);

	skyboxRenderer.Init(camera);
	chunkRenderer.Init(camera);
	guiRenderer.Init(window, camera);

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);

	bool show_demo_window = true;
	bool show_another_window = false;

	while (!glfwWindowShouldClose(window))
	{
		glClearDepth(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double cursorX, cursorY;
		glfwGetCursorPos(window, &cursorX, &cursorY);

		camera.ProcessMouseInput(window, cursorX, cursorY);

		m.lock();
		camera.ProcessKeyInput(window);
		m.unlock();

		skyboxRenderer.Draw(camera);
		chunkRenderer.Draw(camera);
		guiRenderer.Draw(camera);

	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	isWorking = false;
}

