#include "Shader.h"

#include <GL/glew.h>
#include <iostream>

static GLuint CreateShader(const char* text, GLenum shaderType);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const char* errorMsg);

Shader::Shader(const char* vertex, const char* fragment, const char* geometry) {

	program = glCreateProgram();
	shaders[0] = CreateShader(vertex, GL_VERTEX_SHADER);
	glAttachShader(program, shaders[0]);
	shaders[1] = CreateShader(fragment, GL_FRAGMENT_SHADER);
	glAttachShader(program, shaders[1]);

	if (geometry) {
		shaders[2] = CreateShader(geometry, GL_GEOMETRY_SHADER);
		glAttachShader(program, shaders[2]);
	}

	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "Program linking failed");
	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Program validation failed");

}

Shader::~Shader() {

	glDetachShader(program, shaders[0]);
	glDeleteShader(shaders[0]);
	glDetachShader(program, shaders[1]);
	glDeleteShader(shaders[1]);

	if (shaders[2] > 0) {
		glDetachShader(program, shaders[2]);
		glDeleteShader(shaders[2]);
	}

	glDeleteProgram(program);

}

void Shader::bind() {

	glUseProgram(program);

}

unsigned int Shader::createUniform(const char* name) {

	unsigned int index = glGetUniformLocation(program, name);
	uniforms.push_back(index);
	return index;

}

unsigned int Shader::createAttribute(const char* name) {

	glBindAttribLocation(program, attribCount++, name);
	return attribCount - 1;

}

static GLuint CreateShader(const char* text, GLenum shaderType) {

	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) {
		printf("Shader creation failed\n");
		return 0;
	}

	int len = (int)strlen(text);
	glShaderSource(shader, 1, &text, &len);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader compilation failed");

	return shader;

}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const char* errorMsg) {

	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		printf("%s: '%s'\n", errorMsg, error);
	}

}