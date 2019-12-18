#include <renderer/TerrainRenderer.h>

TerrainRenderer::TerrainRenderer(std::mutex &m, TerrainWorld &world, Camera &camera, std::atomic<bool> &isWorking)
	: m(m), world(world), camera(camera), isWorking(isWorking), theSun(0.0f, 0.8f, 0.0f)
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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 420");

	shader = Shader::FromFiles("./data/shader/test-vertex.glsl", "./data/shader/test-fragment.glsl");

	glBindAttribLocation(shader.Id(), 0, "position");

	shader.Link();

	glClearColor(135.0 / 255.0, 206.0 / 255.0, 235.0 / 255.0, 1.0);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	shader.Use();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	//float sunDir = -0.01f;

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(window))
	{
		glClearDepth(GL_DEPTH_BUFFER_BIT);
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

		//if (theSun.y <= -0.8f) {
		//	sunDir = + 0.01f;
		//} else if (theSun.y >= 1.0f) {
		//	sunDir = - 0.01f;
		//}

		//theSun.y += sunDir;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin(" ");    // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	isWorking = false;
}

void TerrainRenderer::DrawSingleTerrainChunk(TerrainChunk &chunk, int &resolution)
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

	shader.SetUniformInt("grassTexture", 0);
	shader.SetUniformInt("rockTexture", 1);
	shader.SetUniformInt("dirtTexture", 2);
	shader.SetUniformInt("snowTexture", 3);

	shader.SetUniformVec3("cameraPosition", camera.GetPosition());
	shader.SetUniformVec3("theSun", theSun);
	shader.SetUniformInt("resolution", resolution);
	shader.SetUniformMat4("projection", camera.GetProjection());
	shader.SetUniformMat4("view", camera.GetView());
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
