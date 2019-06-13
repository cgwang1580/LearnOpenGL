#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <Shader_Helper.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

const unsigned int WIN_WINDTH = 800;
const unsigned int WIN_HEIGHT = 600;

#define MY_MAX_PATH	256
#define USE_SHADER_HELPER

enum MERR_CODE {
	MOK = 0,
	MERR_INVALID_PARAMETER,
	MERR_BAD_STATE,
	MERR_NO_MEMORY
};

const string imagePath = "..\\Resource\\HelloTexture\\container.jpg";
const string imagePath2 = "..\\Resource\\HelloTexture\\awesomeface.png";
const string imagePath3 = "..\\Resource\\HelloTexture\\face.jpg";

unsigned int texture;
unsigned int texture2;
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;

float thresh = 0.5;

float vertices[] = {
	// vertex				texture
	 0.5f,   0.5f, 0.0f,   1.0f, 1.0f,
	 0.5f,  -0.5f, 0.0f,   1.0f, 0.0f,
	-0.5f,  -0.5f, 0.0f,   0.0f, 0.0f,
	-0.5f,   0.5f, 0.0f,   0.0f, 1.0f
};

unsigned int indecies[] = {
	0, 1, 3,
	1, 2, 3
};

float vertices_cube[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

// define camera system
glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0);
glm::vec3 cameraFront = glm::vec3(0.0, 0.0, -1.0);
glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);

const string vertexShaderPath = "Shader/vertex.shader";
const string fragmentShaderPath = "Shader/fragment.shader";
GLFWwindow *window = NULL;

bool keys[1024] = { false };
GLfloat currentTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat takeTime = 0.0f;
GLfloat cameraSpeed = 0.1f;

GLfloat lastXPos = (GLfloat)WIN_WINDTH / 2;
GLfloat lastYPos = (GLfloat)WIN_HEIGHT / 2;
GLfloat sensity = 0.05;
GLfloat yaw = -90.0;
GLfloat pitch = 0.0;
bool firstMouse = true;
GLfloat aspect = 45.0f;

GLFWwindow* initGLFW();

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// add mouse callback function 
void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
	cout << "xPos = " << xPos << " yPos = " << yPos << endl;

	if (firstMouse) {
		lastXPos = xPos;
		lastYPos = yPos;
		firstMouse = false;
	}

	GLfloat offsetX = xPos - lastXPos;
	GLfloat offsetY = lastYPos - yPos;

	offsetX *= sensity;
	offsetY *= sensity;

	lastXPos = xPos;
	lastYPos = yPos;

	pitch += offsetY;
	yaw += offsetX;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (aspect >= 1.0f && aspect <= 45.0f)
		aspect -= yoffset;
	if (aspect <= 1.0f)
		aspect = 1.0f;
	if (aspect >= 45.0f)
		aspect = 45.0f;
}

void processInput(GLFWwindow *window);

void doMovement();

