#include "Light.h"

Light::Light() {

	isChanged = true;

}

void Light::setRange(float amt) {
	isChanged = true;
	range = amt;
}

float Light::getRange() {
	return range;
}

void Light::setColor(glm::vec3 color) {
	isChanged = true;
	this->color = glm::vec4(color, this->color.w);
}

glm::vec3 Light::getColor() {
	return glm::vec3(color);
}

void Light::setIntensity(float amt) {
	isChanged = true;
	color.w = amt;
}

float Light::getIntensity() {
	return color.w;
}