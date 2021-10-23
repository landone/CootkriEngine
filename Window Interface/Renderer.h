#pragma once

#include <list>
#include <glm/vec4.hpp>

#include "UIElement.h"
#include "Display.h"
#include "Shader.h"
#include "Texture.h"
#include "Drawable.h"
#include "Event.h"

class UIElement;
class Shader;

class Renderer : private EventListener {
public:

	Renderer(Shader*, EventManager* parent = nullptr, Display* display = nullptr);
	~Renderer();

	/// <summary>
	/// Set shader to use for drawing elements.
	/// </summary>
	/// <param name="Shader"></param>
	void setShader(Shader*);

	/// <summary>
	/// Set dimensions of output texture.
	/// </summary>
	/// <param name="size"></param>
	void setSize(glm::vec2);

	/// <summary>
	/// Get dimensions of output texture.
	/// </summary>
	/// <returns></returns>
	glm::vec2 getSize();

	/// <summary>
	/// Get shader in use.
	/// </summary>
	/// <returns>Shader</returns>
	Shader* getShader();

	/// <summary>
	/// Given relative and absolute positions, convert and combine them to GL screen coordinates.
	/// </summary>
	/// <param name="relative">Relative coordinates (-1 to 1)</param>
	/// <param name="absolute">Absolute coordinates (pixels)</param>
	/// <returns></returns>
	glm::vec2 makeScreenCoords(glm::vec2 relative, glm::vec2 absolute);

	/// <summary>
	/// Color to clear buffer with.
	/// </summary>
	/// <param name="color"></param>
	void setClearColor(glm::vec4 color);

	/// <summary>
	/// Add a texture output to the frame buffer.
	/// </summary>
	/// <returns>GL Texture ID</returns>
	unsigned int addTexture();

	/// <summary>
	/// Add an existing texture output to the frame buffer.
	/// </summary>
	/// <param name="tex">Texture object to draw to</param>
	void addTexture(Texture tex);

	/// <summary>
	/// Remove an existing texture output from frame buffer.
	/// </summary>
	/// <param name="tex">Texture object to remove</param>
	void removeTexture(Texture tex);

	/// <summary>
	/// Add UIElement to render list.
	/// </summary>
	/// <param name="UIElement">Element to draw.</param>
	void add(UIElement*);

	/// <summary>
	/// Remove UIElement from render list.
	/// </summary>
	/// <param name="UIElement">Element to remove.</param>
	void remove(UIElement*);

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

	/// <summary>
	/// Draw using a specified function with passed data.
	/// </summary>
	/// <param name="func">Custom draw function.</param>
	/// <param name="data">Optional data to pass</param>
	void draw(void(*func)(Renderer*,void*), void* data = nullptr);

private:

	Display* display = nullptr;
	Shader* shader = nullptr;
	unsigned int bufferID = 0;
	glm::vec4 clearColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	std::list<Drawable*> elemList;
	std::list<Texture> textures;
	glm::vec2 dimensions = glm::vec2(1,1);

	void onEvent(Event*) override;

	/// <summary>
	/// Make a new buffer for use.
	/// Deleted on renderer deconstruct.
	/// </summary>
	/// <returns>Buffer ID</returns>
	unsigned int makeBuffer();

	/// <summary>
	/// Prepare objects before calling draw functions.
	/// </summary>
	void prepareToDraw();

};