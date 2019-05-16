#include "DrawTriangle.h"

int main() {

	/*int result = MOK;
	char infoLog[MY_MAX_PATH];*/

	if (!glfwInit()) {
		return -1;
	}
	
	//cout << "vertex shader: " << endl << vertexShaderSource << endl;

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

	int nrAttributes = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	cout << "GL_MAX_VERTEX_ATTRIBS " << nrAttributes << endl;


	// create and compile shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	char *verShader = NULL;
	verShader = new char[MY_MAX_PATH];
	if (!verShader) {
		cout << "verShader is NULL" << endl;
		return MERR_NO_MEMORY;
	}
	strcpy(verShader, vertexShaderSourceTest.c_str());
	printf("vertex shader\n %s\n", verShader);
	glShaderSource(vertexShader, 1, &verShader, NULL);
	glCompileShader(vertexShader);

	// create fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	char *fragShader = NULL;
	fragShader = new char[MY_MAX_PATH];
	if (!fragShader) {
		cout << "fragShader is NULL" << endl;
		return MERR_NO_MEMORY;
	}
	strcpy(fragShader, fragmentShaderSourceTestUniform.c_str());
	printf("fragment shader\n %s\n", fragShader);
	glShaderSource(fragmentShader, 1, &fragShader, NULL);
	glCompileShader(fragmentShader);

	// create shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// link vertex shader and fragment shader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// generate VBO
	glGenBuffers(1, &VBO);
	// generate VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

	// set vertex property
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// set mode as draw line
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(window)) {

		// process
		processInput(window);

		glUseProgram(shaderProgram);

		// set uniform valiable
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		if (-1 == vertexColorLocation) {
			cout << "glGetUniformLocation failed" << endl;
			break;
		}
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	if (verShader) {
		delete []verShader;
	}
	if (fragmentShader) {
		delete[]fragShader;
	}
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