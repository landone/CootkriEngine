#pragma once

#include "Texture.h"
#include "Transform.h"
#include "Event.h"
#include "Display.h"

class Image : public EventListener {
public:

	Image(Display* = nullptr);
	Image(const Texture&, Display* = nullptr);

	//Draw static square vertex array
	static void drawStatic();
	//Draw image to current buffer
	void draw();

	//Set absolute or relative position. (0,0) is center.
	void setPos(const glm::vec2&, bool rel = false);
	//Set absolute or relative scale
	void setSize(const glm::vec2&, bool rel = false);
	//Set rotation in radians
	void setRot(float);
	//Tint image a color
	void setTint(glm::vec3);
	//Tint image a color
	void setTint(float r, float g, float b);
	//Change image's texture
	void setTexture(const Texture&);


	//Get absolute or relative position
	glm::vec2 getPos(bool rel = false);
	//Get absolute or relative scale
	glm::vec2 getSize(bool rel = false);
	//Get rotation in radians
	float getRot();
	//Tint color as vector
	glm::vec3 getTint();
	//Retrieve used texture
	Texture getTexture();

protected:

	Texture texture;

private:

	void onEvent(Event*) override;

	glm::vec2 relPos = glm::vec2(0,0);
	glm::vec2 absPos = glm::vec2(0,0);
	glm::vec2 relSize = glm::vec2(0,0);
	glm::vec2 absSize = glm::vec2(1,1);
	glm::vec3 tint = glm::vec3(1, 1, 1);
	Transform trans;

};