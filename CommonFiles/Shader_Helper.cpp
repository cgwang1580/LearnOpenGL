#include "Shader_Helper.h"

Shader_Helper::Shader_Helper(const string vertexPath, const string fragmentPath) {

	cout << "MyShader begin" << endl;
	
	ifstream vShaderFile;
	ifstream fShaderFile;

	string vertexCode;
	string fragmentCode;

	// enable exception
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	// read shader code from file
	stringstream vShaderStream, fShaderStream;
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		cout << "vertexCode = " << vertexCode << endl << "fragmentCode = " << fragmentCode << endl;
	}
	catch (ifstream::failure e){
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	// compile shader
	unsigned int vertexShader, fragmentShader;
	int result = 0;
	char infoLog[MY_MAX_PATH * 2] = { 0 };

	do {
		// vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		glCompileShader(vertexShader);
		// get compile shader result
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderInfoLog(vertexShader, MY_MAX_PATH * 2, NULL, infoLog);
			cout << "glCompileShader vertexShader error, " << infoLog << endl;
			break;
		}

		// fragment shader 
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragmentShader);
		// get compile shader result
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderInfoLog(fragmentShader, MY_MAX_PATH * 2, NULL, infoLog);
			cout << "glCompileShader fragmentShader error, " << infoLog << endl;
			break;
		}

		// shader program
		progreamId = glCreateProgram();
		glAttachShader(progreamId, vertexShader);
		glAttachShader(progreamId, fragmentShader);
		glLinkProgram(progreamId);
		// get link result
		glGetProgramiv(progreamId, GL_LINK_STATUS, &result);
		if (!result) {
			glGetProgramInfoLog(progreamId, MY_MAX_PATH * 2, NULL, infoLog);
			cout << "glLinkProgram progreamId error, " << infoLog << endl;
			break;
		}

		// delete shader
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	} while (false);
}

void Shader_Helper::use() {
	glUseProgram(progreamId);
}

void Shader_Helper::setBool (const string &name, bool value) const{
	glUniform1i(glGetUniformLocation(progreamId, name.c_str()), value);
}

void Shader_Helper::setInt(const string &name, int value) const {
	glUniform1i(glGetUniformLocation(progreamId, name.c_str()), value);
}

void Shader_Helper::setfloat(const string &name, float value) const {
	glUniform1f(glGetUniformLocation(progreamId, name.c_str()), value);
}

void Shader_Helper::setVec3f(const string &name, float value1, float value2, float value3) const
{
	glUniform3f(glGetUniformLocation(progreamId, name.c_str()), value1, value2, value3);
}