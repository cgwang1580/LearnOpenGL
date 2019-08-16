#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <Shader_Helper.h>

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

const string imagePath3 = "..\\Resource\\HelloTexture\\Face.jpg";
const string imagePath2 = "..\\Resource\\HelloTexture\\awesomeface.png";
const string imagePath = "..\\Resource\\HelloTexture\\awesomeface.png";

unsigned int texture;
unsigned int texture2;
unsigned int VAO;
unsigned int VBO;

unsigned int VAO_plane, VBO_plane;

float thresh = 0.5;

float vertices[] = {
	// vertex			texture
	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

	0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
	1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
	1.0f,  0.5f,  0.0f,  1.0f,  0.0f
};

const string vertexShaderPath = "Shader/vertex.shader";
const string fragmentShaderPath = "Shader/fragment.shader";

GLFWwindow* initGLFW();

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window);
