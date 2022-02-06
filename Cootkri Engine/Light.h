#pragma once

#include "Component.h"

class Light : public Component {
public:

	Light();

	void setRange(float);

	float getRange();

	void setColor(glm::vec3);

	glm::vec3 getColor();

	void setIntensity(float);

	float getIntensity();

private:

	bool isChanged;
	float range = 10.0f;
	glm::vec4 color = glm::vec4(1,1,1,1); //(color.xyz,intensity)

};