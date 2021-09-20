#include <Display.h>
#include <UIShader.h>
#include <Image.h>

#include <MouseEvent.h>

class Tester : public EventListener {
public:

	UIElement* el[2] = { nullptr, nullptr };

	Tester() {
		setParent(Display::getMain());
		addType(EVENTTYPE::DISPLAY_FRAME);
		addType(EVENTTYPE::MOUSE_BUTTON);
	}

protected:

	void onEvent(Event* e) override {
		
		if (e->type == EVENTTYPE::MOUSE_BUTTON) {
			MouseButtonEvent me = *((MouseButtonEvent*)e);
			if (me.press) {
				if (me.btn == MOUSEBUTTON::LEFT) {
				}
				else if (me.btn == MOUSEBUTTON::RIGHT) {
				}
			}
		}
		else {
		}
	}

};

int main() {

	Display disp("Cootkri");
	disp.setResizable(true);

	Image lPanel;
	lPanel.setPos(glm::vec2(150, 150));
	lPanel.setPos(glm::vec2(-1, 0), true);
	lPanel.setSize(glm::vec2(300, -300));
	lPanel.setSize(glm::vec2(0, 2), true);
	lPanel.setTint(glm::vec3(0.8f, 0.8f, 0));

	Image rPanel;
	rPanel.setPos(glm::vec2(-150, 150));
	rPanel.setPos(glm::vec2(1, 0), true);
	rPanel.setSize(glm::vec2(300, -300));
	rPanel.setSize(glm::vec2(0, 2), true);
	rPanel.setTint(glm::vec3(0.8f, 0, 0.8f));

	Image bPanel;
	bPanel.setPos(glm::vec2(0, 150));
	bPanel.setPos(glm::vec2(0, -1), true);
	bPanel.setSize(glm::vec2(0, 300));
	bPanel.setSize(glm::vec2(2, 0), true);
	bPanel.setTint(glm::vec3(0.8f, 0.1f, 0.2f));

	Image tPanel;
	tPanel.setOrigin(ORIGIN::TOP);
	tPanel.setPos(glm::vec2(0, 1), true);
	tPanel.setPos(glm::vec2(0,0));
	tPanel.setSize(glm::vec2(2, 2), true);
	tPanel.setSize(glm::vec2(-600, -300));

	Tester test;
	test.el[0] = &lPanel;
	test.el[1] = &rPanel;

	disp.clear(0, 0, 0, 1);
	while (disp.isOpen()) {
		disp.poll();
		disp.clear();
		tPanel.draw();
		lPanel.draw();
		rPanel.draw();
		bPanel.draw();
		
		disp.swap();
	}

	return 0;

}