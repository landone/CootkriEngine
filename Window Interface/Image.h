#pragma once

#include "Texture.h"
#include "UIElement.h"
#include "Drawable.h"

class Image : public UIElement {
public:

	Image();
	Image(const Texture&);

	bool isStatic = false;
	
	/// <summary>
	/// Draw static square vertex array
	/// </summary>
	static void drawStatic();

	/// <summary>
	/// Draw image to current buffer
	/// </summary>
	/// <param name="Shader"></param>
	void draw(void*) override;

	/// <summary>
	/// Tint image a color
	/// </summary>
	/// <param name="color">Color RGB vector</param>
	void setTint(glm::vec3 color);

	/// <summary>
	/// Change image's texture
	/// </summary>
	/// <param name="tex">Texture to use</param>
	void setTexture(const Texture& tex);

	/// <summary>
	/// Get tint color vector
	/// </summary>
	/// <returns>Color RGB vector</returns>
	glm::vec3 getTint();

	/// <summary>
	/// Retrieve used texture
	/// </summary>
	/// <returns>Texture</returns>
	Texture getTexture();

protected:

	Texture texture;

private:

	void prepareVertexArray();
	void createFullscreenMesh();

	glm::vec3 tint = glm::vec3(1, 1, 1);

};