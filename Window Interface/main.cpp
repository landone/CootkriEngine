#include "Display.h"
#include "KeyboardEvent.h"

class T : EventListener {
public:
	T(Display* d) : EventListener(d) {
		addType(EVENTTYPE::KEYBOARD);
	}
private:
	void onEvent(Event* e) override {
		KEY k = ((KeyboardEvent*)e)->key;
		printf("%s", KeyboardEvent::keyToString(k).c_str());
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

	if (popup.isOpen()) {
		popup.close();
	}

	Display::quit();

	return 0;

}