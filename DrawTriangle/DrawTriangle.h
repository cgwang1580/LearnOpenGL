#ifndef DRAW_TRIANGLE_HEADER
#define DRAW_TRIANGLE_HEADER

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <Shader_Helper.h>
#include "Config.h"

using namespace std;

#define MY_MAX_PATH	256

enum MERR_CODE{
	MOK = 0,
	MERR_INVALID_PARAMETER,
	MERR_BAD_STATE,
	MERR_NO_MEMORY
};

const unsigned int WIN_WINDTH = 800;
const unsigned int WIN_HEIGHT = 600;

// callback function	
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window);

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
};

float vertices2[] = {
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f
};

float vertices3[] = {
	 0.5f,  0.5f, 0.0f,  1.0, 0.0, 0.0,
	 0.5f, -0.5f, 0.0f,  0.0, 1.0, 0.0,
	-0.5f, -0.5f, 0.0f,  0.0, 0.0, 1.0,
	-0.5f,  0.5f, 0.0f,  1.0, 1.0, 0.0
};

unsigned int indecies[] = {
	0, 1, 3,
	1, 2, 3
};

const string vertexShaderSource = "\
#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
void main()\n\
{\n\
	gl_Position = vec4 (aPos.x, aPos.y, aPos.z, 1.0);\n\
}";

const string fragmentShaderSource = "\
#version 330 core\n\
out vec4 FragColor;\n\
void main()\n\
{\n\
	FragColor  = vec4 (1.0f, 0.5f, 0.2f, 1.0f);\n\
}";

const string vertexShaderSourceTest = "\
#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
out vec4 vertexColor;\n\
void main()\n\
{\n\
	gl_Position = vec4 (aPos.x, aPos.y, aPos.z, 1.0);\n\
	vertexColor = vec4 (0.5, 0.0, 0.0, 1.0);\n\
}";

const string fragmentShaderSourceTest = "\
#version 330 core\n\
out vec4 FragColor;\n\
in vec4 vertexColor;\n\
void main()\n\
{\n\
	FragColor  = vertexColor;\n\
}";

const string fragmentShaderSourceTestUniform = "\
#version 330 core\n\
out vec4 FragColor;\n\
uniform vec4 ourColor;\n\
void main()\n\
{\n\
	FragColor  = ourColor;\n\
}";

const string vertexShaderSourceColor = "\
#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
layout (location = 1) in vec3 aColor;\n\
out vec3 vertexColor;\n\
void main()\n\
{\n\
	gl_Position = vec4 (aPos.x, aPos.y, aPos.z, 1.0);\n\
	vertexColor = aColor;\n\
}";

const string fragmentShaderSourceColor = "\
#version 330 core\n\
out vec4 FragColor;\n\
in vec3 vertexColor;\n\
void main()\n\
{\n\
	FragColor  = vec4 (vertexColor, 1.0);\n\
}";

const string VertexShaderPath = "Shader\\vertex.shader";
const string FragmentShaderPath = "Shader\\fragment.shader";

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

#endif // !DRAW_TRIANGLE_HEADER



