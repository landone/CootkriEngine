#include "UIElement.h"

#define getPixelRatio()		(((Display*)getParent())->getPixelToScreen())

UIElement::UIElement(Display* disp) {

	if (disp == nullptr) {
		disp = Display::getMain();
	}
	setParent(disp);
	addType(EVENTTYPE::DISPLAY_RESIZE);

	//Transform defaults with scale of 1, zero this
	trans.setScale(glm::vec3(0, 0, 0));

}

void UIElement::onEvent(Event* e) {

	if (e->type == EVENTTYPE::DISPLAY_RESIZE) {
		//Fix absolute coordinates on resize
		glm::vec2 ratio = getPixelRatio();
		if (absPos != glm::vec2(0, 0)) {
			trans.setPos(glm::vec3(relPos + absPos * ratio, 0));
		}
		if (absSize != glm::vec2(0, 0)) {
			trans.setScale(glm::vec3(relSize + absSize * ratio, 1));
		}
	}

}

void UIElement::setPos(const glm::vec2& pos, bool rel) {

	if (rel) {
		relPos = pos;
	}
	else {
		absPos = pos;
	}

	glm::vec2 ratio = getPixelRatio();
	trans.setPos(glm::vec3(relPos + absPos * ratio, 0));

}

void UIElement::setSize(const glm::vec2& scale, bool rel) {

	if (rel) {
		relSize = scale;
	}
	else {
		absSize = scale;
	}

	glm::vec2 ratio = getPixelRatio();
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

bool UIElement::collides(glm::vec2 pt) {

	//Convert pixel coords to screen coords
	pt = pt * getPixelRatio();
	pt.x -= 1.0f;
	pt.y = -pt.y + 1;

	glm::vec2 pts[4];
	getTransPts(pts);
	glm::vec2 axis[2];
	glm::vec2 interval[2];
	getAxisAndIntervals(pts, axis, interval);

	float ptPrj = glm::dot(axis[0], pt);

	if (ptPrj < interval[0][0] || ptPrj > interval[0][1]) {
		return false;
	}

	ptPrj = glm::dot(axis[1], pt);

	if (ptPrj < interval[1][0] || ptPrj > interval[1][1]) {
		return false;
	}

	return true;

}

bool UIElement::collides(UIElement& el) {

	glm::vec2 aPts[4];
	glm::vec2 bPts[4];
	getTransPts(aPts);
	el.getTransPts(bPts);

	glm::vec2 axis[2];
	glm::vec2 interval[2];

	getAxisAndIntervals(aPts, axis, interval);
	for (int i = 0; i < 2; ++i) {
		//Calculate shape projection interval
		float proj = glm::dot(axis[i], bPts[0]);
		glm::vec2 prjInt = glm::vec2(proj,proj);
		for (int j = 1; j < 4; ++j) {
			proj = glm::dot(axis[i], bPts[j]);
			if (proj < prjInt.x) {
				prjInt.x = proj;
			}
			else if (proj > prjInt.y) {
				prjInt.y = proj;
			}
		}

		//All projections must overlap
		if (!isIntervalOverlap(interval[i], prjInt)) {
			return false;
		}
	}

	getAxisAndIntervals(bPts, axis, interval);
	for (int i = 0; i < 2; ++i) {
		//Calculate shape projection interval
		float proj = glm::dot(axis[i], aPts[0]);
		glm::vec2 prjInt = glm::vec2(proj, proj);
		for (int j = 1; j < 4; ++j) {
			proj = glm::dot(axis[i], aPts[j]);
			if (proj < prjInt.x) {
				prjInt.x = proj;
			}
			else if (proj > prjInt.y) {
				prjInt.y = proj;
			}
		}

		//All projections must overlap
		if (!isIntervalOverlap(interval[i], prjInt)) {
			return false;
		}
	}

	//All intervals overlap, polygons intersect
	return true;

}

void UIElement::getAxisAndIntervals(glm::vec2 pts[4], glm::vec2 axis[2], glm::vec2 interval[2]) {

	axis[0] = glm::normalize(pts[1] - pts[0]);
	axis[1] = glm::normalize(pts[2] - pts[0]);

	interval[0] = glm::vec2(glm::dot(axis[0], pts[0]), glm::dot(axis[0], pts[1]));
	interval[1] = glm::vec2(glm::dot(axis[1], pts[0]), glm::dot(axis[1], pts[2]));

	//Ensure order is (min,max)
	if (interval[0][0] > interval[0][1]) {
		float swap = interval[0][0];
		interval[0][0] = interval[0][1];
		interval[0][1] = swap;
	}

	if (interval[1][0] > interval[1][1]) {
		float swap = interval[1][0];
		interval[1][0] = interval[1][1];
		interval[1][1] = swap;
	}

}

void UIElement::getTransPts(glm::vec2 pts[4]) {

	glm::mat4 matr = trans.getMatrix();
	pts[0] = glm::vec2(matr * glm::vec4(-0.5, -0.5, 0, 1));//Bottom left
	pts[1] = glm::vec2(matr * glm::vec4(0.5, -0.5, 0, 1));//Bottom right
	pts[2] = glm::vec2(matr * glm::vec4(-0.5, 0.5, 0, 1));//Top left
	pts[3] = glm::vec2(matr * glm::vec4(0.5, 0.5, 0, 1));//Top right

}

bool UIElement::isIntervalOverlap(glm::vec2 int1, glm::vec2 int2) {

	if (int1[0] < int2[0]) {
		return (int1[1] > int2[0]);
	}

	return (int2[1] > int1[0]);

}