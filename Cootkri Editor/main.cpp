#include <Display.h>
#include <UIShader.h>
#include <Image.h>
#include <MouseEvent.h>
#include <Renderer.h>
#include <Text.h>
#include <GeometryShader.h>
#include <LightShader.h>
#include <Model.h>
#include <Camera.h>

#include <ctime>
#include <glm/gtc/matrix_transform.hpp>

int main() {

	srand(clock());

	Display disp("Cootkri Engine");
	disp.setResizable(true);

	Renderer uiRender(&UIShader::get());
	GeometryShader* geomShader = new GeometryShader();
	LightShader* lightShader = new LightShader();
	Renderer geomRender(geomShader);
	Renderer lightRender(lightShader);

	Texture geometryTex;
	geometryTex.setID(geomRender.addTexture());
	Texture normalTex;
	normalTex.setID(geomRender.addTexture());
	Texture colorTex;
	colorTex.setID(geomRender.addTexture());

	Texture lightTex;
	lightTex.setID(lightRender.addTexture());
	lightShader->setMaps(geometryTex.getID(), normalTex.getID(), colorTex.getID());

	Image lPanel;
	lPanel.isStatic = true;
	lightRender.add(&lPanel);

	Image mPanel;
	mPanel.setOrigin(UIElement::ORIGIN::CENTER);
	mPanel.setPos(glm::vec2(0, 0));
	mPanel.setPos(glm::vec2(0, 0), true);
	mPanel.setSize(glm::vec2(0, 0));
	mPanel.setSize(glm::vec2(2, 2), true);
	mPanel.setTint(glm::vec3(1, 1, 1));
	mPanel.setTexture(lightTex);
	uiRender.add(&mPanel);

	Model mdl("models/Majora.obj");
	Entity ent;
	Entity ent2;
	Camera cam;
	Light light;
	light.setRange(10);
	ent2.getTrans().setPos(glm::vec3(0, 0, -2));
	ent2.addComponent(cam);
	ent2.addComponent(light);
	ent.addComponent(mdl);
	Transform& trans = ent.getTrans();
	trans.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	trans.setPos(glm::vec3(0, 0, -0.5));

	geomRender.add(&ent);
	geomRender.add(&ent2);
	geomRender.setClearColor(glm::vec4(0, 0, 0, 0));

	uiRender.setClearColor(glm::vec4(0, 0.3, 0.3, 1));

	Text text("test");
	uiRender.add(&text);

	//Make renderers corect size
	disp.refreshScreenSize();

	trans.setRot(glm::vec3(0, 3.1415f, 0));
	while (disp.isOpen()) {
		disp.poll();
		text.setText(std::to_string((int)disp.getFPS()));
		trans.rotate(glm::vec3(0, 3.1415f * disp.getDelta(), 0));
		geomRender.draw();
		lightShader->setCameraPos(cam.getEntity()->getTrans().getPos());
		lightShader->setLight(light);
		lightRender.draw();
		uiRender.draw();
		disp.swap();
	}

	return 0;

}