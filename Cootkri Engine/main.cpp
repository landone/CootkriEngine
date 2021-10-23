#include <Display.h>
#include <UIShader.h>
#include <Image.h>
#include <MouseEvent.h>
#include <Renderer.h>
#include <Text.h>

#include <ctime>

class Tester : public EventListener {
public:

	Tester() {
		setParent(Display::getMain());
	}

protected:

	void onEvent(Event* e) override {
	}

};

int main() {

	Display disp("Cootkri Engine");
	disp.setResizable(true);

	Renderer uiRender(&UIShader::get());

	Image lPanel;
	lPanel.setPos(glm::vec2(150, 150));
	lPanel.setPos(glm::vec2(-1, 0), true);
	lPanel.setSize(glm::vec2(300, -300));
	lPanel.setSize(glm::vec2(0, 2), true);
	lPanel.setTint(glm::vec3(0.4f, 0.4f, 0.4f));
	uiRender.add(&lPanel);

	Image rPanel;
	rPanel.setPos(glm::vec2(-150, 150));
	rPanel.setPos(glm::vec2(1, 0), true);
	rPanel.setSize(glm::vec2(300, -300));
	rPanel.setSize(glm::vec2(0, 2), true);
	rPanel.setTint(glm::vec3(0.4f, 0.4f, 0.4f));
	uiRender.add(&rPanel);

	Image bPanel;
	bPanel.setPos(glm::vec2(0, 150));
	bPanel.setPos(glm::vec2(0, -1), true);
	bPanel.setSize(glm::vec2(0, 300));
	bPanel.setSize(glm::vec2(2, 0), true);
	bPanel.setTint(glm::vec3(0.3f, 0.3f, 0.3f));
	uiRender.add(&bPanel);

	Image tPanel;
	tPanel.setOrigin(UIElement::ORIGIN::TOP);
	tPanel.setPos(glm::vec2(0, 1), true);
	tPanel.setPos(glm::vec2(0,0));
	tPanel.setSize(glm::vec2(2, 2), true);
	tPanel.setSize(glm::vec2(-600, -300));
	tPanel.setTint(glm::vec3(0.2f, 0.2f, 0.2f));
	uiRender.add(&tPanel);

	Text text;
	text.setTint(glm::vec3(0, 1, 0));
	text.setOrigin(UIElement::ORIGIN::TOP);
	text.setPos(glm::vec2(0, 1), true);
	text.setPos(glm::vec2(0, 0));
	text.setSize(glm::vec2(0, 75));
	text.setSize(glm::vec2(2, 0), true);
	text.setText("TEST STRING");
	uiRender.add(&text);
	

	clock_t time = clock();
	int frameCt = 0;
	while (disp.isOpen()) {
		disp.poll();
		uiRender.draw();
		
		disp.swap();
		/*++frameCt;
		if (frameCt >= 10) {
			clock_t newTime = clock();
			float delta = (newTime - time) / (float)CLOCKS_PER_SEC;
			float fps = frameCt / delta;
			printf("FPS: %f\n", fps);
			frameCt = 0;
			time = newTime;
		}*/
	}

	return 0;

}