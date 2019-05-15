#include "HelloOpenGL.h"
using namespace std;

int main() {
	if (!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(WIN_WINDTH, WIN_HEIGHT, "HelloOpenGL", NULL, NULL);
	if (NULL == window) {
		cout << "glfwCreateWindow failed" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// register callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to intialize GLAD" << endl;
		return -1;
	}
	// render loop
	while (!glfwWindowShouldClose (window)){

		// process
		processInput(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	//system("pause");
	return MOK;
}

void processInput(GLFWwindow *window) {
	
	glClearColor(0.1f, 0.2f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// get input 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}