#include "HelloTexture.h"

int main() {

	int result = MOK;
	GLFWwindow *window = initGLFW();

	if (NULL == window) {
		cout << "initGLFW failed, result = " << result << endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#ifdef USE_SHADER_HELPER
	Shader_Helper shaderHelper(vertexShaderPath, fragmentShaderPath);
#endif // USE_SHADER_HELPER

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

	// set vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// set color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof (float)));
	glEnableVertexAttribArray(1);

	// set texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// VAO_Plane
	glGenVertexArrays(1, &VAO_plane);
	glGenBuffers(1, &VBO_plane);
	glGenBuffers(1, &EBO_plane);
	glBindVertexArray(VAO_plane);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_plane);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_plane);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);


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

	unsigned char* data_rgba = (unsigned char *)malloc(imgWidth * imgHeight * 4);
	if (nullptr == data_rgba) {
		std::cout << "data_rgba malloc failed" << std::endl;
		return -1;
	}
	for (int row = 0; row < imgHeight; ++row) {
		for (int col = 0; col < imgWidth; ++col) {
			int r = *(data + row * imgWidth * 3 + col * 3);
			int g = *(data + row * imgWidth * 3 + col * 3 + 1);
			int b = *(data + row * imgWidth * 3 + col * 3 + 2);
			*(data_rgba + row * imgWidth * 4 + col * 4) = r;
			*(data_rgba + row * imgWidth * 4 + col * 4 + 1) = g;
			*(data_rgba + row * imgWidth * 4 + col * 4 + 2) = b;
			float gray = r * 0.299f + g * 0.587f + b * 0.114f;
			if (gray < 100) {
				*(data_rgba + row * imgWidth * 4 + col * 4 + 3) = 0;
			}
			else {
				*(data_rgba + row * imgWidth * 4 + col * 4 + 3) = 120;
			}
		}
	}

	if (data_rgba) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_rgba);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else{
		cout << "stbi_load image failed" << endl;
		return -1;
	}
	stbi_image_free(data);
	free(data_rgba);
	data_rgba = nullptr;

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

	unsigned char* data_rgba2 = (unsigned char *)malloc(imgWidth2 * imgHeight2 * 4);
	if (nullptr == data_rgba2) {
		std::cout << "data_rgba malloc failed" << std::endl;
		return -1;
	}
	for (int row = 0; row < imgHeight2; ++row) {
		for (int col = 0; col < imgWidth2; ++col) {
			int r = *(data2 + row * imgWidth2 * 3 + col * 3);
			int g = *(data2 + row * imgWidth2 * 3 + col * 3 + 1);
			int b = *(data2 + row * imgWidth2 * 3 + col * 3 + 2);
			*(data_rgba2 + row * imgWidth2 * 4 + col * 4) = r;
			*(data_rgba2 + row * imgWidth2 * 4 + col * 4 + 1) = g;
			*(data_rgba2 + row * imgWidth2 * 4 + col * 4 + 2) = b;
			float gray = r * 0.299f + g * 0.587f + b * 0.114f;
			/*if (gray < 100) {
				*(data_rgba2 + row * imgWidth2 * 4 + col * 4 + 3) = 0;
			}
			else {
				*(data_rgba2 + row * imgWidth2 * 4 + col * 4 + 3) = 150;
			}*/
			*(data_rgba2 + row * imgWidth2 * 4 + col * 4 + 3) = 255;
		}
	}

	if (data_rgba2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth2, imgHeight2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_rgba2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "stbi_load image2 failed" << endl;
		return -1;
	}

	stbi_image_free(data2);
	free(data_rgba2);
	data_rgba2 = nullptr;

#ifdef USE_SHADER_HELPER
	shaderHelper.use();
	shaderHelper.setInt("texture1", 0);
#endif

	while (!glfwWindowShouldClose(window)) {
		
		processInput(window);

		// active texture
		glActiveTexture(GL_TEXTURE0);
		// bind Texture
		glBindTexture(GL_TEXTURE_2D, texture);

		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2);

#ifdef USE_SHADER_HELPER
		shaderHelper.use();
		// get input 
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			thresh -= 0.05;
			if (thresh <= 0.0) {
				thresh = 0.0;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			thresh += 0.05;
			if (thresh >= 1.0) {
				thresh = 1.0;
			}
		}
		shaderHelper.setfloat("thresh", thresh);
#endif // USE_SHADER_HELPER

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(VAO_plane);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);

	glDeleteBuffers(1, &VBO_plane);
	glDeleteVertexArrays(1, &VAO_plane);
	glDeleteBuffers(1, &EBO_plane);

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
