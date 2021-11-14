#pragma once

#include "Component.h"

class Camera : public Component {
public:

	Camera();

	glm::mat4 getViewMatrix();

	void setFOV(float);

	void setAspect(float);

	void setNear(float);

	void setFar(float);

	void preDraw(void*) override;

private:

	float near = 0.001f;
	float far = 10000.0f;
	float aspect = 16.0 / 9.0f;
	float fovY = 3.1415f / 3.0f;

	glm::mat4 perspective = glm::mat4(1.0f);
	glm::mat4 cameraMat = glm::mat4(1.0f);
	glm::mat4 viewMat = glm::mat4(1.0f);
	bool perspectiveChanged = true;

};