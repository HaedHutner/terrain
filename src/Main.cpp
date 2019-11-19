#include <iostream>
#include <vector>
#include <thread>

#include <HeightMapGenerator.h>

// #include <glad/glad.h>
// #include <glfw/glfw3.h>
// #include <glm/glm.hpp>
// #include <FastNoise/FastNoise.h>
// #include <stb/stb_image.h>

// const GLfloat SQUARE_VERTICES[] = {
//     -0.5f, -0.5f, 0.0f,
//     +0.5f, -0.5f, 0.0f,
//     +0.5f, +0.5f, 0.0f,
//     -0.5f, +0.5f, 0.0f
// };

// const GLuint SQUARE_INDICES[] = {
//     0, 1, 2, 
//     0, 3, 2
// };

int main()
{
	std::thread t([]() {});

    HeightMapGenerator generator = HeightMapGenerator();
    tools::Matrix<float> result = generator.generateHeightMap({0, 0}, {16, 16});

    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            std::cout << result[x][y] << " ";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
    // GLFWwindow *window;

    // // GLFW Error callback
    // glfwSetErrorCallback([](int error, const char *desc) { fputs(desc, stderr); });

    // if (!glfwInit())
    // {
    //     exit(EXIT_FAILURE);
    // }

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // window = glfwCreateWindow(600, 600, "Terrain", nullptr, nullptr);

    // if (!window)
    // {
    //     glfwTerminate();
    //     exit(EXIT_FAILURE);
    // }

    // glfwMakeContextCurrent(window);

    // // Window resize callback
    // glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height){
    //     glViewport(0, 0, width, height);
    // });

    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize OpenGL context" << std::endl;
    //     return -1;
    // }

    // printf("OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);

    // GLuint vao, vbo, ebo;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    // glGenBuffers(1, &vbo);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(SQUARE_VERTICES), SQUARE_VERTICES, GL_STATIC_DRAW);

    // glGenBuffers(1, &ebo);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SQUARE_INDICES), SQUARE_INDICES, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glBindVertexArray(0);

    // glClearColor(135.0 / 255.0, 206.0 / 255.0, 235.0 / 255.0, 1.0);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // while (!glfwWindowShouldClose(window))
    // {

    //     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //     glEnableVertexAttribArray(0);

    //     glBindVertexArray(vao);
    //     glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    //     glDrawElements(GL_TRIANGLES, sizeof(SQUARE_INDICES), GL_UNSIGNED_INT, NULL);

    //     glDisableVertexAttribArray(0);

    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }

    // glfwDestroyWindow(window);

    // glfwTerminate();

    // exit(EXIT_SUCCESS);
}