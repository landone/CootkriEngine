#include <Display.h>
#include <UIShader.h>
#include <Image.h>

int main() {

	Display disp("Cootkri");

	Image lPanel;
	lPanel.setPos(glm::vec2(150, 0));
	lPanel.setPos(glm::vec2(-1, 0), true);
	lPanel.setSize(glm::vec2(300, 0));
	lPanel.setSize(glm::vec2(0, 2), true);
	lPanel.setTint(0.8f, 0.8f, 0.8f);

	disp.clear(0, 0, 0, 1);
	while (disp.isOpen()) {
		disp.poll();
		disp.clear();
		lPanel.draw();
		disp.swap();
	}

	return 0;

}