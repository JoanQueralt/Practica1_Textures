#pragma once
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL.h>
// GLM Mathematics
#include<glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

class Camara
{
private:
	vec3 cameraPos;
	vec3 cameraFront;
	vec3 cameraUp;
	GLfloat Deltatime;
	GLfloat Lastframe;
	GLfloat LastMx;
	GLfloat LastMy;
	GLfloat Sensitivity;
	GLboolean firstMouse;
	GLfloat PITCH;
	GLfloat YAW;
	GLfloat FOV;

public:
	Camara(vec3 position, vec3 direction, GLfloat sensitivity, GLfloat fov);
	void DoMovement(GLFWwindow * window, Camara cam);
	void MouseMove(GLFWwindow* window, double xpos, double ypos, Camara cam);
	void MouseScroll(GLFWwindow* window, double xScroll, double yScroll, Camara cam);
	mat4 LookAt(const vec3& Eye, const vec3& Center, const vec3& Up);
	GLfloat GetFOV(Camara cam);

	~Camara();
};

