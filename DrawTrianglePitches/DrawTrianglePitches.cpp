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

#define USE_SHADER_HELPER
#define WIN_WINDTH 1080
#define WIN_HEIGHT 1920

using namespace std;

GLfloat pointRadius = 5.0f;

float vertices[]{
	// 0, 1, 2, 3, 4, 5, 6
	 0.25, 0.25,  0,  1.0, 1.0, 1.0,
	 0,    0.125, 0,  1.0, 1.0, 1.0,
	-0.25, 0.25,  0,  1.0, 1.0, 1.0,
	 0,    0,     0,  1.0, 1.0, 1.0,
	-0.5, -0.25,  0,  1.0, 1.0, 1.0,
	 0,   -0.125, 0,  1.0, 1.0, 1.0,
	 0.5, -0.25,  0,  1.0, 1.0, 1.0
};

float vertices_line[]{
	 0.5,  0.5, 0,    1.0, 1.0, 1.0,
	 0.5, -0.5, 0,    1.0, 1.0, 1.0,
	-0.5, -0.5, 0,    1.0, 1.0, 1.0,
	-0.5,  0.5, 0,    1.0, 1.0, 1.0
};

float vertices_bg[]{
	 0.5,  0.5, 0, 0.0, 0.0, 0.0,
	-0.5,  0.5, 0, 0.0, 0.0, 0.0,
	 0.5, -0.5, 0, 0.0, 0.0, 0.0,
	 0.5, -0.5, 0, 0.0, 0.0, 0.0,
	-0.5, -0.5, 0, 0.0, 0.0, 0.0,
	-0.5,  0.5, 0, 0.0, 0.0, 0.0
};

unsigned int indecies[] = {
	0, 1,
	0, 2,
	0, 3,
	0, 4,
	0, 5,
	0, 6,
	1, 2,
	1, 3,
	1, 4,
	1, 5,
	1, 6,
	2, 3,
	2, 4,
	2, 5,
	2, 6,
	3, 4,
	3, 5,
	3, 6,
	4, 5,
	4, 6,
	5, 6,
};

GLFWwindow* initGLFW();
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	if (aspect >= 1.0f && aspect <= 45.0f)
//		aspect -= yoffset;
//	if (aspect <= 1.0f)
//		aspect = 1.0f;
//	if (aspect >= 45.0f)
//		aspect = 45.0f;
//}

int main()
{
	GLFWwindow *window = NULL;
	window = initGLFW();
	if (NULL == window) {
		cout << "initGLFW failed" << endl;
		return -1;
	}

	string vertexShaderPath = "vertex.shader";
	string fragmentShaderPath = "fragment.shader";
#ifdef USE_SHADER_HELPER
	Shader_Helper shaderHelper(vertexShaderPath, fragmentShaderPath);
#endif // USE_SHADER_HELPER

	GLuint VAO_bg, VBO_bg;
	glGenVertexArrays(1, &VAO_bg);
	glBindVertexArray(VAO_bg);

	glGenBuffers(1, &VBO_bg);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_bg);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_line), vertices_line, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof (GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof (float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	// create texture
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = nullptr;
	data = stbi_load("green.jpg", &width, &height, &nrChannels, 0);
	if (nullptr != data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else {
		cout << "stbi_load failed" << endl;
	}
	stbi_image_free(data);

	while (!glfwWindowShouldClose(window)) {
		//processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// draw our first triangle
		shaderHelper.use();

		GLfloat lineWidth = 1.0f;
		glLineWidth(lineWidth);
		GLfloat pointRadius = 50.0f;
		//glPointSize(pointRadius);
		shaderHelper.setfloat("pointSize", pointRadius);
		shaderHelper.setBool("is_sprite", true);
		

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_LINES, 42, GL_UNSIGNED_INT, 0);

		glDrawArrays(GL_POINTS, 0, 7);
		glBindVertexArray(0);

		glBindVertexArray(VAO_bg); 
		glDrawArrays(GL_LINES, 0, 4);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glDrawArrays(GL_POINTS, 0, 4);
		glBindVertexArray(0);
		glDisable(GL_PROGRAM_POINT_SIZE);
		glDisable(GL_BLEND);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();

	return 0;
}



GLFWwindow* initGLFW() {
	if (!glfwInit()) {
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIN_WINDTH, WIN_HEIGHT, "HelloCamera", NULL, NULL);
	if (NULL == window) {
		cout << "glfwCreateWindow failed" << endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	// register callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to intialize GLAD" << endl;
		return NULL;
	}

	int nrAttributes = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	cout << "GL_MAX_VERTEX_ATTRIBS " << nrAttributes << endl;

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPosCallback(window, mouse_callback);

	//glfwSetScrollCallback(window, scroll_callback);

	return window;
}

//void processInput(GLFWwindow *window) {
//
//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// get input 
//	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
//		keys[GLFW_KEY_UP] = true;
//	}
//	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
//		keys[GLFW_KEY_DOWN] = true;
//	}
//	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
//		keys[GLFW_KEY_LEFT] = true;
//	}
//	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
//		keys[GLFW_KEY_RIGHT] = true;
//	}
//
//	//GLfloat cameraSpeed = 0.05f;
//	// get input 
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}

//void doMovement() {
//
//	if (keys[GLFW_KEY_UP])
//		cameraPos += cameraSpeed * cameraFront;
//	if (keys[GLFW_KEY_DOWN])
//		cameraPos -= cameraSpeed * cameraFront;
//	if (keys[GLFW_KEY_RIGHT]) {
//		rotateAngle -= 10.0f;
//	}
//	if (keys[GLFW_KEY_LEFT]) {
//		rotateAngle += 10.0f;
//	}
//	for (int i = 0; i < 1024; ++i) {
//		keys[i] = false;
//	}
//}