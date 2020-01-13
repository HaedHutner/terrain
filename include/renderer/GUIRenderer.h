#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

#include <imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <renderer/Camera.h>

class GUIRenderer {

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

public:

	GUIRenderer();

	void Init(GLFWwindow *window, Camera &camera);

	void Draw(Camera &camera);

};

#endif // !GUI_RENDERER_H
