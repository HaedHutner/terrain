#ifndef _CAMERA_H
#define _CAMERA_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
	int screenX, screenY;

	double last_frame = 0;
	double delta_time = 0;

	double speed_modifyer = 2.5f;
	double mouse_sensitivity = 0.2f;

	glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_direction = glm::normalize(camera_position - camera_target);

	glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 camera_right = glm::normalize(glm::cross(camera_up, camera_direction));

	glm::mat4 projection;

	bool first_mouse = true;
	double yaw = -90.0;    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	double pitch = 0.0;
	double last_x;
	double last_y;
	double field_of_view = 90.0;
public:
	enum MoveDirection {
		UP,
		DOWN,
		FORWARD,
		BACK,
		LEFT,
		RIGHT
	};

	Camera();

	Camera(float fov, float cameraSpeed, float mouseSensitivity, int screenX, int screenY,
		glm::vec3 beginningCoords = { 0, 0, 0 }, glm::vec3 beginningDirection = { 0, 0, 0 },
		glm::vec2 beginningRotation = { 0, 0 });

	int GetScreenX();

	int GetScreenY();

	glm::mat4 GetView();

	glm::mat4 GetProjection();

	glm::vec3 GetPosition();

	void UpdateProjection(int screenX, int screenY);

	void ResetCursor(float x, float y);

	void Move(MoveDirection dir, float speed);

	void ProcessKeyInput(GLFWwindow* window);

	void ProcessMouseInput(GLFWwindow* window, double x, double y);
};

#endif // !_CAMERA_H
