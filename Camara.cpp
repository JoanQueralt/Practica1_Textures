#include "Camara.h"



Camara::Camara(vec3 position, vec3 direction, GLfloat sensitivity, GLfloat fov)
{
}

void Camara::DoMovement(GLFWwindow * window)
{
	GLfloat speedCamera = 3.0f * Deltatime;



	int StatusW = glfwGetKey(window, GLFW_KEY_W);
	int StatusS = glfwGetKey(window, GLFW_KEY_S);
	int StatusA = glfwGetKey(window, GLFW_KEY_A);
	int StatusD = glfwGetKey(window, GLFW_KEY_D);

	if (StatusW == GLFW_PRESS) {
		cameraPos += speedCamera * cameraFront;

	}
	if (StatusS == GLFW_PRESS) {

		cameraPos -= speedCamera * cameraFront;
	}
	if (StatusA == GLFW_PRESS) {

		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speedCamera;
	}
	if (StatusD == GLFW_PRESS) {

		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speedCamera;
	}
}

bool firstMouse = true;
void Camara::MouseMove(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse)
	{
		LastMx = xpos;
		LastMy = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - LastMx;
	GLfloat yoffset = LastMy -ypos; // Reversed since y-coordinates go from bottom to left
	LastMx = xpos;
	LastMy = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	YAW += xoffset;
	PITCH += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (PITCH > 89.0f) {
		PITCH = 89.0f;
	}
	if (PITCH < -89.0f) {
		PITCH = -89.0f;
	}


	glm::vec3 front;
	front.x = cos(glm::radians(YAW)) * cos(glm::radians(YAW));
	front.y = sin(glm::radians(PITCH));
	front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
	cameraFront = glm::normalize(front);

}

void Camara::MouseScroll(GLFWwindow * window, double xScroll, double yScroll, Camara cam)
{
	if (cam.FOV >= 1.0f && cam.FOV <= 45.0f)
		cam.FOV -= yScroll;
	if (cam.FOV <= 1.0f)
		cam.FOV = 1.0f;
	if (cam.FOV >= 45.0f)
		cam.FOV = 45.0f;
}

mat4 Camara::LookAt(const vec3& Eye, const vec3& Center, const vec3& Up)
{
	mat4 Matrix;

	vec3 X, Y, Z;
	Z = Eye - Center;
	normalize(Z);
	Y = Up;
	X = cross(Y, Z);
	Y = cross(Z, X);
	normalize(X);
	normalize(Y);

	Matrix[0][0] = X.x;
	Matrix[1][0] = X.y;
	Matrix[2][0] = X.z;
	Matrix[3][0] = -dot(X, Eye);
	Matrix[0][1] = Y.x;
	Matrix[1][1] = Y.y;
	Matrix[2][1] = Y.z;
	Matrix[3][1] = -dot(Y, Eye);
	Matrix[0][2] = Z.x;
	Matrix[1][2] = Z.y;
	Matrix[2][2] = Z.z;
	Matrix[3][2] = -dot(Z, Eye);
	Matrix[0][3] = 0;
	Matrix[1][3] = 0;
	Matrix[2][3] = 0;
	Matrix[3][3] = 1.0f;

	
	return mat4(Matrix);
}

GLfloat Camara::GetFOV(Camara cam)
{

	return GLfloat(cam.FOV);
}


Camara::~Camara()
{
}
