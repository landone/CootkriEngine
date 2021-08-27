#pragma once

#include "Texture.h"
#include "UIElement.h"

class Image : public UIElement {
public:

	Image(Display* = nullptr);
	Image(const Texture&, Display* = nullptr);
	
	/// <summary>
	/// Draw static square vertex array
	/// </summary>
	static void drawStatic();

	/// <summary>
	/// Draw image to current buffer
	/// </summary>
	void draw() override;

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

	glm::vec3 tint = glm::vec3(1, 1, 1);

};