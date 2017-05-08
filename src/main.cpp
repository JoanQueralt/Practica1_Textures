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
// Other includes
#include "Shader.h"

using namespace std;
using namespace glm;

int screenWithd, screenHeight;


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, int mode, int  value);
void funcionScroll(GLFWwindow* window, double xpos, double ypos);
void DoMovement(GLFWwindow* window);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

GLfloat rotationX = 10.0f;
GLfloat rotationY = 0.0f;

GLfloat opacidad = 0.0f;
GLboolean texture = true;


glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUP = glm::vec3(0.0f, 1.0f, 0.0f);

GLfloat yawVar = -90.0f;
GLfloat pitchVar = 0.0f;
GLfloat lastX = 400.0f;
GLfloat lastY = 400.0f;
GLfloat fov = 45.0f;

//time

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;




// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica1", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Set the required callback functions
	
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, funcionScroll);
	
	

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);


	// Build and compile our shader program
	shader Shader("./src/textureVertex.vertexshader.vertexshader", "./src/textureFragment.fragmentshader.fragmentshader");


	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat VertexBufferCube[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f , -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	vec3 CubesPositionBuffer[] = {
		vec3(0.0f ,  0.0f,  0.0f),
		vec3(2.0f ,  5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f , -0.4f, -3.5f),
		vec3(-1.7f,  3.0f, -7.5f),
		vec3(1.3f , -2.0f, -2.5f),
		vec3(1.5f ,  2.0f, -2.5f),
		vec3(1.5f ,  0.2f, -1.5f),
		vec3(-1.3f,  1.0f, -1.5f)
	};

	glfwGetTime();

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferCube), VertexBufferCube, GL_STATIC_DRAW);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glEnable(GL_DEPTH_TEST);

	glBindVertexArray(0); // Unbind VAO


	// Load and create a texture 
	GLuint texture1;
	GLuint texture2;

	// Texture 1

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("./src/moon.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	// Unbind texture when done, so we won't accidentily mess up our texture.

	// Texture 2

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("./src/awesome.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		//deltaTime
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement(window);
		//mouse_callback(window, lastX, lastY);


		// Render
		// Clear the color buffer
		glClearColor(0.8f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		


		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(Shader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(Shader.Program, "ourTexture2"), 1);

		glUniform1f(glGetUniformLocation(Shader.Program, "opacidad"), opacidad);

		// Activate shader
		Shader.Use();

		//Camera

		// Camera/View transformation
		glm::mat4 view;
		view = lookAt(cameraPosition, cameraPosition + cameraFront, cameraUP);
		// Projection 
		glm::mat4 projection;
		projection = glm::perspective(fov, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(Shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(Shader.Program, "view");
		GLint projLoc = glGetUniformLocation(Shader.Program, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw container
		glBindVertexArray(VAO);
		for (int i = 0; i < 10; i++) {

			if (i == 0) {
				glm::mat4 model2;
				model2 = glm::translate(model2, CubesPositionBuffer[i]);
				
				model2 = glm::rotate(model2, 1.0f, glm::vec3(rotationX, rotationY, 0.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else {
				glm::mat4 model2;
				model2 = glm::translate(model2, CubesPositionBuffer[i]);
				GLfloat angle = 1.0f * i;
				model2 = glm::rotate(model2, (GLfloat)glfwGetTime()*angle, vec3(0.7f, 1.3f, 5.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
				glDrawArrays(GL_TRIANGLES, 0, 36);


			}
			

		}
	
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		opacidad = 0.0f;
		
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		opacidad = 1.0f;
	}

	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {

		++rotationX;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {

		--rotationX;
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {

		++rotationY;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {

		--rotationY;
	}

	
}

void DoMovement(GLFWwindow* window) {

	GLfloat speedCamera = 3.0f * deltaTime;



	int StatusW = glfwGetKey(window, GLFW_KEY_W);
	int StatusS = glfwGetKey(window, GLFW_KEY_S);
	int StatusA = glfwGetKey(window, GLFW_KEY_A);
	int StatusD = glfwGetKey(window, GLFW_KEY_D);

	if (StatusW == GLFW_PRESS) {
		cameraPosition += speedCamera * cameraFront;

	}
	if (StatusS == GLFW_PRESS) {

		cameraPosition -= speedCamera * cameraFront;
	}
	if (StatusA == GLFW_PRESS) {

		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUP)) * speedCamera;
	}
	if (StatusD == GLFW_PRESS) {

		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUP)) * speedCamera;
	}

}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {


	
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yawVar += xoffset;
	pitchVar += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitchVar > 89.0f) {
		pitchVar = 89.0f;
	}
	if (pitchVar < -89.0f) {
		pitchVar = -89.0f;
	}
		

	glm::vec3 front;
	front.x = cos(glm::radians(yawVar)) * cos(glm::radians(pitchVar));
	front.y = sin(glm::radians(pitchVar));
	front.z = sin(glm::radians(yawVar)) * cos(glm::radians(pitchVar));
	cameraFront = glm::normalize(front);


}


void funcionScroll(GLFWwindow* window, double xoffset, double yoffset) {

	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;

}
mat4 LookAtFunction(const vec3& Eye, const vec3& Center, const vec3& Up)
{
	mat4 Matrix;

	vec3 X, Y, Z;
	Z = Eye - Center;
	normalize(Z);
	Y = Up;
	X = cross(Y, Z);
	Y = cross(Z,X);
	normalize(X);
	normalize(Y);

	Matrix[0][0] = X.x;
	Matrix[1][0] = X.y;
	Matrix[2][0] = X.z;
	Matrix[3][0] = -dot(X,Eye);
	Matrix[0][1] = Y.x;
	Matrix[1][1] = Y.y;
	Matrix[2][1] = Y.z;
	Matrix[3][1] = -dot(Y,Eye);
	Matrix[0][2] = Z.x;
	Matrix[1][2] = Z.y;
	Matrix[2][2] = Z.z;
	Matrix[3][2] = -dot(Z,Eye);
	Matrix[0][3] = 0;
	Matrix[1][3] = 0;
	Matrix[2][3] = 0;
	Matrix[3][3] = 1.0f;

	return Matrix;
}