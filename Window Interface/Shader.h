#pragma once

#include <vector>

#include "Renderer.h"

class Renderer;


class Shader {
public:

	Shader() {}
	Shader(const char* vertex, const char* frag, const char* geom = nullptr);
	~Shader();

	//Create a new buffer
	static unsigned int createBuffer();
	//Remove a buffer from memory
	static void deleteBuffer(unsigned int id);
	//Set buffer as current
	static void bindBuffer(unsigned int);

	//Load a shader using strings
	void load(const char* vertex, const char* frag, const char* geom = nullptr);
	/// <summary>
	/// Prepare shader for use in a renderer.
	/// </summary>
	/// <param name="renderer"></param>
	virtual void bind(Renderer*);
	//Allocate a uniform
	unsigned int createUniform(const char* name);
	//Allocate an attribute
	unsigned int createAttribute(const char* name);

	//Retrieve shader program index
	unsigned int getProgram() { return program; }
	//Return current framebuffer
	unsigned int getBuffer();

protected:

	//Remember uniform indices
	std::vector<unsigned int> uniforms;

private:

	unsigned int program = 0;
	unsigned int shaders[3] = { 0 };
	unsigned int attribCount = 0;

};