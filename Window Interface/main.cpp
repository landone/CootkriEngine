#include "Display.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"

class T : EventListener {
public:
	T(Display* d) : EventListener(d) {
		addType(EVENTTYPE::MOUSEBUTTON);
	}
private:
	void onEvent(Event* e) override {
		if (e->type == EVENTTYPE::MOUSEBUTTON) {
			MouseButtonEvent& ke = *((MouseButtonEvent*)e);
			if (ke.press && ke.btn == MOUSEBUTTON::MIDDLE) {
				printf("(%d, %d)\n", ke.pos[0], ke.pos[1]);
			}
		}
	}
};

int main() {
	
	Display display("Main window");
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