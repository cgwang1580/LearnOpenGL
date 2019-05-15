#ifndef HELLO_OPENGL_HEADER
#define HELLO_OPENGL_HEADER

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
//#pragma once

enum MERR_CODE{
	MOK = 0,
	MERR_INVALID_PARAMETER,
	MERR_BAD_STATE
};

const unsigned int WIN_WINDTH = 800;
const unsigned int WIN_HEIGHT = 600;

// callback function	
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window);

#endif // !HELLO_OPENGL_HEADER



