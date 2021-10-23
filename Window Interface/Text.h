#pragma once

#include "Image.h"

class Text : public Image {
public:

	Text();
	Text(const std::string&);
	~Text();

	void setText(const std::string&);

private:

	//Draws text to the image's texture
	void drawText();

	/// <summary>
	/// Custom draw function passed to renderer.
	/// Used for drawing text, not the resulting image.
	/// </summary>
	static void customDraw(Renderer*, void*);

	std::string contents;

};