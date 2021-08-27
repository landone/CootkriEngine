#include <Display.h>
#include <UIShader.h>
#include <Image.h>

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
	rPanel.setTint(glm::vec3(0, 0.8f, 0.8f));

	disp.clear(0, 0, 0, 1);
	while (disp.isOpen()) {
		disp.poll();
		disp.clear();
		lPanel.draw();
		rPanel.draw();
		bPanel.draw();
		disp.swap();
	}

	return 0;

}