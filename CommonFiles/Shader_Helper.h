/***
** this is a class for shader 
** created by chauncy_wang at 5/7/2019
***/

#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "glad/glad.h"

#define MY_MAX_PATH		256

using namespace std;

class Shader_Helper {

public:
	unsigned int progreamId;

	// generator
	Shader_Helper(const string vertexPath, const string fragmentPath);

	// use glprograme
	void use();

	// uniform function
	void setBool(const string &name, bool value) const;
	void setInt(const string &name, int value) const;
	void setfloat(const string &name, float value) const;
};