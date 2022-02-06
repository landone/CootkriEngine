#pragma once

#include "Shader.h"
#include "Light.h"

class LightShader : public Shader {
public:

	LightShader();

	void bind(Renderer*) override;

	void setCameraPos(glm::vec3);

	void setMaps(unsigned int pos, unsigned int norm, unsigned int color);

	void setLight(Light);

private:

	enum UNIFORMS {
		POS_MAP, NORM_MAP, COLOR_MAP,
		LIGHT_COLOR, LIGHT_POS, LIGHT_SIZE,
		CAM_POS,
		MAX_UNIFORMS
	};
	unsigned int uniforms[(int)UNIFORMS::MAX_UNIFORMS];

	unsigned int maps[3] = { 0, 1, 2 };

};