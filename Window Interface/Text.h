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

	std::string contents;

};