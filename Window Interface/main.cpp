#include "Display.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "DisplayEvent.h"
#include "BasicShader.h"
#include "Image.h"
#include "Texture.h"

class T : EventListener {
public:
	T(Display* d) : EventListener(d) {
		addType(EVENTTYPE::MOUSE_BUTTON);
		addType(EVENTTYPE::DISPLAY_RESIZE);
	}
private:
	void onEvent(Event* e) override {
		if (e->type == EVENTTYPE::MOUSE_BUTTON) {
			MouseButtonEvent& ke = *((MouseButtonEvent*)e);
			if (ke.press && ke.btn == MOUSEBUTTON::MIDDLE) {
				printf("(%d, %d)\n", ke.pos[0], ke.pos[1]);
			}
		}
		else if (e->type == EVENTTYPE::DISPLAY_RESIZE) {
			DisplayResizeEvent& de = *((DisplayResizeEvent*)e);
			printf("Resized: (%d, %d)\n", de.size[0], de.size[1]);
		}
	}
};

int main() {
	
	Display display("Main window");
	display.setResizable(true);
	display.clear(0.2f, 0.2f, 0.6f, 1.0f);
	BasicShader shader;
	shader.bind();
	Texture tex("./textures/test.png");
	Texture tex2("./textures/test2.png");
	Image img(tex);
	Image img2(tex2);
	
	T Test(&display);

	while (display.isOpen()) {

		Display::poll();
		display.clear();
		shader.setTransMatrix(img.getMatrix());
		img.draw();
		shader.setTransMatrix(img2.getMatrix());
		img2.draw();
		display.swap();

	}

	Display::quit();

	return 0;

}