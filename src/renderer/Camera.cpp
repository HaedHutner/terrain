#include <renderer/Camera.h>

Camera::Camera()
{
}

Camera::Camera(float fov, float cameraSpeed, float mouseSensitivity, int screenX, int screenY,
	glm::vec3 beginningCoords, glm::vec3 beginningDirection, glm::vec2 beginningRotation)
	: camera_position(beginningCoords), camera_direction(beginningDirection), camera_target(beginningRotation, 0),
	field_of_view(fov), speed_modifyer(cameraSpeed), mouse_sensitivity(mouseSensitivity), screenX(screenX), screenY(screenY) {
	UpdateProjection(screenX, screenY);
}

int Camera::GetScreenX()
{
	return screenX;
}

int Camera::GetScreenY()
{
	return screenY;
}

glm::mat4 Camera::GetView() {
	return glm::lookAt(camera_position, camera_position + camera_front, camera_up);
}

glm::mat4 Camera::GetProjection() {
	return projection;
}

glm::vec3 Camera::GetPosition() { return camera_position; }

void Camera::UpdateProjection(int screenX, int screenY) {
	projection = glm::perspective(glm::radians(field_of_view), (double) screenX / screenY, 0.1, 255.0);
}

void Camera::ResetCursor(float x, float y) {
	last_x = x;
	last_y = y;
}

void Camera::Move(MoveDirection dir, float speed) {
	switch (dir) {
	case UP:
		camera_position += speed * camera_up;
		break;
	case DOWN:
		camera_position -= speed * camera_up;
		break;
	case FORWARD:
		camera_position += speed * camera_front;
		break;
	case BACK:
		camera_position -= speed * camera_front;
		break;
	case LEFT:
		camera_position -= glm::normalize(glm::cross(camera_front, camera_up)) * speed;
		break;
	case RIGHT:
		camera_position += glm::normalize(glm::cross(camera_front, camera_up)) * speed;
		break;
	}

	//Log::info("Camera: %.6f, %.6f, %.6f", camera_position.x, camera_position.z, camera_position.y);
}

void Camera::ProcessKeyInput(GLFWwindow* window) {
	double currentFrame = glfwGetTime();
	delta_time = currentFrame - last_frame;
	last_frame = currentFrame;

	double speed = speed_modifyer * delta_time;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) speed *= 10.0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Move(FORWARD, speed);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Move(BACK, speed);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Move(LEFT, speed);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Move(RIGHT, speed);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Move(UP, speed);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Move(DOWN, speed);
	}
}

void Camera::ProcessMouseInput(GLFWwindow* window, double x, double y) {
	if (first_mouse) {
		last_x = x;
		last_y = y;
		first_mouse = false;
	}

	double xOffset = x - last_x;
	double yOffset = last_y - y;

	xOffset *= mouse_sensitivity;
	yOffset *= mouse_sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 front;
	front.x = (float)cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = (float)sin(glm::radians(pitch));
	front.z = (float)sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	camera_front = glm::normalize(front);

	last_x = x;
	last_y = y;
}
