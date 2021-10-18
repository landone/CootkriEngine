#pragma once

#include <list>
#include <glm/vec4.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Drawable.h"

class Renderer {
public:

	Renderer(Shader*, unsigned int bufferID = 0);

	/// <summary>
	/// Set shader to use for drawing elements.
	/// </summary>
	/// <param name="Shader"></param>
	void setShader(Shader*);

	/// <summary>
	/// Set buffer to draw elements to.
	/// </summary>
	/// <param name="bufferID"></param>
	void setBuffer(unsigned int bufferID);

	/// <summary>
	/// Make a new buffer for use.
	/// NOT DELETED ON ITS OWN.
	/// </summary>
	/// <returns>Buffer ID</returns>
	unsigned int makeBuffer();

	/// <summary>
	/// Return ID of current buffer.
	/// </summary>
	/// <returns>Buffer ID</returns>
	unsigned int getBuffer();

	/// <summary>
	/// Color to clear buffer with.
	/// </summary>
	/// <param name="color"></param>
	void setClearColor(glm::vec4 color);

	/// <summary>
	/// Add drawable to render list. (No protection for repeats)
	/// </summary>
	/// <param name="Drawable">Element to draw.</param>
	void add(Drawable*);

	/// <summary>
	/// Remove drawable from render list.
	/// </summary>
	/// <param name="Drawable">Element to remove.</param>
	void remove(Drawable*);

	/// <summary>
	/// Draw all elements in list.
	/// </summary>
	void draw();

private:

	Shader* shader = nullptr;
	unsigned int bufferID = 0;
	glm::vec4 clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	std::list<Drawable*> elemList;

};