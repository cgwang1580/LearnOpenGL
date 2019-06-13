#include "HelloCamera.h"

int main() {

	window = initGLFW();
	if (NULL == window) {
		cout << "initGLFW failed" << endl;
		return -1;
	}

#ifdef USE_SHADER_HELPER
	Shader_Helper shaderHelper(vertexShaderPath, fragmentShaderPath);
#endif // USE_SHADER_HELPER

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);*/

	// set vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// set color attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// set texture attribute
	/*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/

	glBindVertexArray(0);  // Unbind VAO

						   // load image, create texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set texture proterty
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// read image
	int imgWidth = 0;
	int imgHeight = 0;
	int nChannels = 0;
	unsigned char* data = NULL;
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(imagePath.c_str(), &imgWidth, &imgHeight, &nChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "stbi_load image failed" << endl;
		return -1;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

									 // load texture2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int imgWidth2 = 0;
	int imgHeight2 = 0;
	int nChannels2 = 0;
	unsigned char* data2 = NULL;
	stbi_set_flip_vertically_on_load(true);
	data2 = stbi_load(imagePath3.c_str(), &imgWidth2, &imgHeight2, &nChannels2, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth2, imgHeight2, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "stbi_load image2 failed" << endl;
		return -1;
	}
	stbi_image_free(data2);
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_DEPTH_TEST);

	// get view port test
	GLint dim[4];
	glGetIntegerv(GL_VIEWPORT, dim);


#ifdef USE_SHADER_HELPER
	shaderHelper.use();
	shaderHelper.setInt("texture1", 0);
	shaderHelper.setInt("texture2", 1);
#endif // USE_SHADER_HELPER

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		currentTime = static_cast<GLfloat>(glfwGetTime());
		takeTime = currentTime - lastTime;
		//cameraSpeed = takeTime * 10000000000.0f * cameraSpeed;
		cout << "lastTime = " << lastTime << "  currentTime = " << currentTime << "  takeTime = " << takeTime << "  cameraSpeed = " << cameraSpeed << endl;

		doMovement();

		// active texture
		glActiveTexture(GL_TEXTURE0);
		// bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Create transformations
		// make sure to initialize matrix to identity matrix first, important!!!
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 perspective = glm::mat4(1.0f);
		perspective = glm::perspective(45.0f, (float)WIN_WINDTH / WIN_HEIGHT, 0.1f, 100.0f);

		// Get matrix's uniform location and set matrix
		GLint transformLoc = glGetUniformLocation(shaderHelper.progreamId, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		GLint viewLoc = glGetUniformLocation(shaderHelper.progreamId, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLint perspectiveLoc = glGetUniformLocation(shaderHelper.progreamId, "projection");
		glUniformMatrix4fv(perspectiveLoc, 1, GL_FALSE, glm::value_ptr(perspective));

		glBindVertexArray(VAO);

		for (int i = 0; i < 10; ++i) {
			glm::mat4 model = glm::mat4(1.0);
			model = glm::translate(model, cubePositions[i]);
			GLfloat angel = 20.0f * i;
			if (i%4 == 0) {
				angel = (GLfloat)glfwGetTime();
			}
			model = glm::rotate(model, angel, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

		lastTime = static_cast<float> (glfwGetTime());
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &EBO);

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

	return window;
}

void processInput(GLFWwindow *window) {

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// get input 
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		keys[GLFW_KEY_UP] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		keys[GLFW_KEY_DOWN] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		keys[GLFW_KEY_LEFT] = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		keys[GLFW_KEY_RIGHT] = true;
	}

	//GLfloat cameraSpeed = 0.05f;
	// get input 
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	/*if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}*/

}

void doMovement(){

	if (keys[GLFW_KEY_UP])
		cameraPos += cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_DOWN])
		cameraPos -= cameraSpeed * cameraFront;
	if (keys[GLFW_KEY_RIGHT])
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (keys[GLFW_KEY_LEFT])
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	for (int i = 0; i < 1024; ++i) {
		keys[i] = false;
	}
}

