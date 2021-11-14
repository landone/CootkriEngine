#include "Transform.h"

#include <glm/gtx/transform.hpp>

glm::mat4 Transform::getMatrix() {

	bool anyChange = false;
	if (changed[0]) {
		anyChange = true;
		posMat = glm::translate(position);
		changed[0] = false;
	}
	if (changed[1]) {
		anyChange = true;
		glm::mat4 rotXMat = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMat = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMat = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
		rotMat = rotZMat * rotYMat * rotXMat;
		changed[1] = false;
	}
	if (changed[2]) {
		anyChange = true;
		scaleMat = glm::scale(scale);
		changed[2] = false;
	}
	if (anyChange) {
		matrix = posMat * rotMat * scaleMat;
	}
	return matrix;

}

bool Transform::isChanged() {

	return changed[0] || changed[1] || changed[2];

}

void Transform::setPos(const glm::vec3& p) {

	position = p;
	changed[0] = true;

}

void Transform::setRot(const glm::vec3& r) {

	rotation = r;
	changed[1] = true;

}

void Transform::rotate(const glm::vec3& r) {

	rotation += r;
	changed[1] = true;

}

void Transform::setScale(const glm::vec3& s) {

	scale = s;
	changed[2] = true;

}

glm::vec3 Transform::getPos() {
	return position;
}

glm::vec3 Transform::getRot() {
	return rotation;
}

glm::mat4 Transform::getRotMatrix() {
	return rotMat;
}

glm::vec3 Transform::getScale() {
	return scale;
}