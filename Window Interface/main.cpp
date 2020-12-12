#include "Display.h"

int main() {
	
	Display display;
	display.clear(0.2f, 0.2f, 0.6f, 1.0f);

	while (display.isOpen()) {

		display.update();
		display.clear();

	}

	return 0;

}