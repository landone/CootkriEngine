#include "Display.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "DisplayEvent.h"

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
	Display popup(300, 100, "Other Window");
	display.clear(0.2f, 0.2f, 0.6f, 1.0f);
	popup.clear(0.6f, 0.2f, 0.2f, 1.0f);
	
	T Test(&display);

	while (display.isOpen() || popup.isOpen()) {

		if (display.isOpen()) {
			display.swap();
			display.clear();
		}
		if (popup.isOpen()) {
			popup.swap();
			popup.clear();
		}
		Display::poll();

	}

	Display::quit();

	return 0;

}