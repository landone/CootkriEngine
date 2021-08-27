#include "UIElement.h"

UIElement::UIElement(Display* disp) {

	if (disp == nullptr) {
		disp = Display::getMain();
	}
	setParent(disp);
	addType(EVENTTYPE::DISPLAY_RESIZE);

}

void UIElement::onEvent(Event* e) {

	//Fix absolute coordinates on resize
	glm::vec2 ratio = ((Display*)getParent())->getPixelToScreen();
	if (absPos != glm::vec2(0, 0)) {
		trans.setPos(glm::vec3(relPos + absPos * ratio, 0));
	}
	if (absSize != glm::vec2(0, 0)) {
		trans.setScale(glm::vec3(relSize + absSize * ratio, 1));
	}

}

void UIElement::setPos(const glm::vec2& pos, bool rel) {

	if (rel) {
		relPos = pos;
	}
	else {
		absPos = pos;
	}

	glm::vec2 ratio = ((Display*)getParent())->getPixelToScreen();
	trans.setPos(glm::vec3(relPos + absPos * ratio, 0));

}

void UIElement::setSize(const glm::vec2& scale, bool rel) {

	if (rel) {
		relSize = scale;
	}
	else {
		absSize = scale;
	}

	glm::vec2 ratio = ((Display*)getParent())->getPixelToScreen();
	trans.setScale(glm::vec3(relSize + absSize * ratio, 1));

}

void UIElement::setRot(float rad) {

	trans.setRot(glm::vec3(0, 0, rad));

}

glm::vec2 UIElement::getPos(bool rel) {

	return (rel ? relPos : absPos);

}

glm::vec2 UIElement::getSize(bool rel) {

	return (rel ? relSize : absSize);

}

float UIElement::getRot() {

	return trans.getRot().z;

}

glm::mat4 UIElement::getMatrix() {

	return trans.getMatrix();

}