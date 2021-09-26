#include "UIElement.h"

#define getPixelRatio()		(((Display*)getParent())->getPixelToScreen())
#define getScreenSpace()	(((Display*)getParent())->getScreenSpace())

typedef UIElement::Vertex Vertex;

static std::vector<Vertex> g_vertices{
	//Center
	Vertex{ glm::vec3(-0.5f,-0.5f,0), glm::vec2(0,0) },
	Vertex{ glm::vec3(0.5f,-0.5f,0), glm::vec2(1,0) },
	Vertex{ glm::vec3(0.5f,0.5f,0), glm::vec2(1,1) },
	Vertex{ glm::vec3(-0.5f,0.5f,0), glm::vec2(0,1) }
};

static const std::vector<unsigned int> g_indices{
	0, 1, 2, 2, 3, 0
};

static const glm::vec3 g_offsets[] = {
			glm::vec3(0,0,0),//Center
			glm::vec3(0,-0.5f,0),//Top
			glm::vec3(0,0.5f,0),//Bottom
			glm::vec3(-0.5f,0,0),//Right
			glm::vec3(0.5f,0,0),//Left
			glm::vec3(-0.5f,-0.5f,0),//TopRight
			glm::vec3(-0.5f,0.5f,0),//BottomRight
			glm::vec3(0.5f,-0.5f,0),//TopLeft
			glm::vec3(0.5f,0.5f,0),//BottomLeft
};

UIElement::UIElement(EventManager* evtM) {

	if (evtM == nullptr) {
		evtM = Display::getMain();
	}
	setParent(evtM);
	addType(EVENTTYPE::DISPLAY_RESIZE);

	//Transform defaults with scale of 1, zero this
	trans.setScale(glm::vec3(0, 0, 0));

}

glm::vec3 UIElement::getOriginOffset(ORIGIN o) {

	return g_offsets[(int)o];

}

const std::vector<Vertex>& UIElement::getVertices() {

	return g_vertices;

}

const std::vector<unsigned int>& UIElement::getIndices() {

	return g_indices;

}

void UIElement::onEvent(Event* e) {

	if (e->type == EVENTTYPE::DISPLAY_RESIZE) {
		//Fix absolute coordinates on resize
		glm::vec2 ratio = getPixelRatio();
		glm::vec2 space = getScreenSpace() / 2.0f;
		trans.setPos(glm::vec3(relPos * space + absPos * ratio, 0));
		trans.setScale(glm::vec3(relSize * space + absSize * ratio, 1));
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
	glm::vec2 space = getScreenSpace() / 2.0f;
	trans.setPos(glm::vec3(relPos * space + absPos * ratio, 0));

}

void UIElement::setSize(const glm::vec2& scale, bool rel) {

	if (rel) {
		relSize = scale;
	}
	else {
		absSize = scale;
	}

	glm::vec2 ratio = getPixelRatio();
	glm::vec2 space = getScreenSpace() / 2.0f;
	trans.setScale(glm::vec3(abs(relSize * space + absSize * ratio), 1));

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

UIElement::ORIGIN UIElement::getOrigin() {
	return origin;
}

void UIElement::setOrigin(UIElement::ORIGIN ori) {

	origin = ori;

}

bool UIElement::collides(glm::vec2 pt) {

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
	glm::vec4 offs = glm::vec4(getOriginOffset(origin), 1.0f);
	pts[0] = glm::vec2(matr * (glm::vec4(-0.5, -0.5, 0, 1) + offs));//Bottom left
	pts[1] = glm::vec2(matr * glm::vec4(0.5, -0.5, 0, 1) + offs);//Bottom right
	pts[2] = glm::vec2(matr * glm::vec4(-0.5, 0.5, 0, 1) + offs);//Top left
	pts[3] = glm::vec2(matr * glm::vec4(0.5, 0.5, 0, 1) + offs);//Top right

}

bool UIElement::isIntervalOverlap(glm::vec2 int1, glm::vec2 int2) {

	if (int1[0] < int2[0]) {
		return (int1[1] > int2[0]);
	}

	return (int2[1] > int1[0]);

}