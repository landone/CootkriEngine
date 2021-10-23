#pragma once

#include "Shader.h"

class Shader;

class Drawable {
public:

	/// <summary>
	/// Abstracted OpenGL draw call.
	/// </summary>
	/// <param name="Shader"></param>
	virtual void draw(Shader*) = 0;

};