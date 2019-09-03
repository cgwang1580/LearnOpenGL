#include "HelloColor.h"

int main() {

	GLFWwindow *window = initGLFW();

	if (NULL == window) {
		return -1;
	}

#ifdef USE_SHADER_HELPER
	Shader_Helper lightShaderHelper(vertexShaderPath, fragmentShaderPath);
	Shader_Helper lambShaderHelper(vertexLambShaderPath, fragmentLambShaderPath);
#endif // USE_SHADER_HELPER

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// create for light vertex
	glGenVertexArrays(1, &lambVAO);
	glBindVertexArray(lambVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	
	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIN_WINDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

#ifdef USE_SHADER_HELPER
		lightShaderHelper.use();
		lightShaderHelper.setVec3f("objectColor", 1.0f, 0.5f, 0.31f);
		lightShaderHelper.setVec3f("lightColor", 1.0f, 1.0f, 1.0f);

		// set light, view/projection transfomations
		lightShaderHelper.setMat4("projection", projection);
		lightShaderHelper.setMat4("view", view);

		// world transformation
		lightShaderHelper.setMat4("model", model);
#endif
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glBindVertexArray(0);

		// draw lamb 
#ifdef USE_SHADER_HELPER
		lambShaderHelper.use();
		lambShaderHelper.setMat4("projection", projection);
		lambShaderHelper.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lambPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lambShaderHelper.setMat4("model", model);
#endif // USE_SHADER_HELPER
		
		glBindVertexArray(lambVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &lambVAO);
	glDeleteVertexArrays(1, &lambVAO);
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

	GLFWwindow* window = glfwCreateWindow(WIN_WINDTH, WIN_HEIGHT, "HelloTexture", NULL, NULL);
	if (NULL == window) {
		cout << "glfwCreateWindow failed" << endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	// register callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to intialize GLAD" << endl;
		return NULL;
	}

	int nrAttributes = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	cout << "GL_MAX_VERTEX_ATTRIBS " << nrAttributes << endl;

	return window;
}

void processInput(GLFWwindow *window) {

	glClearColor(0.1f, 0.2f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// get input 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
