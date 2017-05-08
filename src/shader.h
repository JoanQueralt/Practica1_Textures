#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

class shader{
public:
	GLuint Program;
	shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~shader();

	void Use();
};

