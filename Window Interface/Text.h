#pragma once

#include "Image.h"

class Text : public Image {
public:

	Text();
	~Text();

	void setText(const std::string&);

private:

	//Draws text to the iamge's texture
	void drawText();

	std::string contents;
	unsigned int buffer = 0;

};