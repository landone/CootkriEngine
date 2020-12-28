#pragma once

class Shader {
public:

	Shader(const char* vertex, const char* fragment, const char* geometry = nullptr);
	~Shader();

	void bind();
	unsigned int createUniform(const char* name);
	unsigned int bindAttribute(const char* name);

	unsigned getProgram() { return program; }

private:

	unsigned int program = 0;
	unsigned int shaders[3] = { 0 };
	unsigned int attribCount = 0;

};