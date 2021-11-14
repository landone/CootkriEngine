#pragma once

class Drawable {
public:

	/// <summary>
	/// Abstracted OpenGL draw call.
	/// </summary>
	/// <param name="Shader"></param>
	virtual void draw(void* shader) = 0;

	/// <summary>
	/// Called before draw calls.
	/// </summary>
	/// <param name="Shader"></param>
	virtual void preDraw(void* shader) {}

};