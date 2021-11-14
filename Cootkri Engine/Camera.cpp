#include "Camera.h"

#include "GeometryShader.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {

	isDrawable = true;

}

glm::mat4 Camera::getViewMatrix() {

	if (perspectiveChanged) {
		perspective = glm::perspective(fovY, aspect, near, far);
		perspectiveChanged = false;
	}
	Transform* trans = getTrans();
	if (trans) {
		glm::mat4 transMat = trans->getMatrix();
		glm::vec3 lookAt = transMat * glm::vec4(0, 0, 1, 1);
		glm::vec3 up = glm::vec4(0, 1, 0, 1);
		cameraMat = glm::lookAt(trans->getPos(), lookAt, up);
	}
	viewMat = perspective * cameraMat;
	return viewMat;

}

void Camera::preDraw(void* shdr) {

	GeometryShader& shader = *(GeometryShader*)shdr;
	shader.setViewMatrix(getViewMatrix());

}

void Camera::setFOV(float fov) {

	fovY = fov;
	perspectiveChanged = true;

}

void Camera::setAspect(float ratio) {

	aspect = ratio;
	perspectiveChanged = true;

}

void Camera::setNear(float dist) {

	near = dist;
	perspectiveChanged = true;

}

void Camera::setFar(float dist) {

	far = dist;
	perspectiveChanged = true;

}