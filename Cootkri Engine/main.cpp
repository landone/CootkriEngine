#include <Display.h>
#include <UIShader.h>
#include <Image.h>
#include <MouseEvent.h>
#include <Renderer.h>
#include <Text.h>
#include "GeometryShader.h"
#include "Model.h"
#include "Camera.h"

#include <ctime>
#include <glm/gtc/matrix_transform.hpp>

int main() {

	srand(clock());

	Display disp("Cootkri Engine");
	disp.setResizable(true);

	Renderer uiRender(&UIShader::get());
	GeometryShader* geomShader = new GeometryShader();
	Renderer geomRender(geomShader);

	Texture geometryTex;
	geometryTex.setID(geomRender.addTexture());
	Texture normalTex;
	normalTex.setID(geomRender.addTexture());
	Texture colorTex;
	colorTex.setID(geomRender.addTexture());

	Image lPanel;
	lPanel.setOrigin(UIElement::ORIGIN::RIGHT);
	lPanel.setPos(glm::vec2(-205, 0));
	lPanel.setPos(glm::vec2(0, 0), true);
	lPanel.setSize(glm::vec2(400, 300));
	lPanel.setSize(glm::vec2(0, 0), true);
	lPanel.setTint(glm::vec3(1, 1, 1));
	lPanel.setTexture(geometryTex);
	uiRender.add(&lPanel);

	Image mPanel;
	mPanel.setOrigin(UIElement::ORIGIN::CENTER);
	mPanel.setPos(glm::vec2(0, 0));
	mPanel.setPos(glm::vec2(0, 0), true);
	mPanel.setSize(glm::vec2(400, 300));
	mPanel.setSize(glm::vec2(0, 0), true);
	mPanel.setTint(glm::vec3(1, 1, 1));
	mPanel.setTexture(colorTex);
	uiRender.add(&mPanel);

	Image rPanel;
	rPanel.setOrigin(UIElement::ORIGIN::LEFT);
	rPanel.setPos(glm::vec2(205, 0));
	rPanel.setPos(glm::vec2(0, 0), true);
	rPanel.setSize(glm::vec2(400, 300));
	rPanel.setSize(glm::vec2(0, 0), true);
	rPanel.setTint(glm::vec3(1, 1, 1));
	rPanel.setTexture(normalTex);
	uiRender.add(&rPanel);

	Model mdl("models/Majora.obj");
	Entity ent;
	Entity ent2;
	Camera cam;
	ent2.getTrans().setPos(glm::vec3(0, 0, -2));
	ent2.addComponent(cam);
	ent.addComponent(mdl);
	Transform& trans = ent.getTrans();
	trans.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	//trans.setScale(glm::vec3(1.2f, 1.2f, 1.2f));
	trans.setPos(glm::vec3(0, -0.5, -0.5));

	geomRender.add(&ent);
	geomRender.add(&ent2);
	geomRender.setClearColor(glm::vec4(0.4, 0.4, 0.4, 1));
	geomRender.setSize(glm::vec2(400,300));

	
	while (disp.isOpen()) {
		disp.poll();
		trans.rotate(glm::vec3(0, 3.1415f / 360.0f, 0));
		geomRender.draw();
		uiRender.draw();
		disp.swap();
	}

	return 0;

}