#include "Display.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "DisplayEvent.h"
#include "UIShader.h"
#include "Image.h"
#include "Texture.h"

int main() {
	
	Display display("Main window");
	display.setResizable(true);
	display.clear(0.2f, 0.2f, 0.6f, 1.0f);
	UIShader& shader = UIShader::get();
	shader.bind();
	Texture tex("./textures/test.png");
	Texture tex2("./textures/test2.png");
	Image img(tex);
	img.setTint(1, 0, 0);
	img.setSize(glm::vec2(64,64));
	Image img2(tex2);
	img2.setSize(glm::vec2(256, 256));
	img2.setTint(0.8f, 0.8f, 0.4f);
	img2.setTexture(tex2);

	while (display.isOpen()) {

		Display::poll();
		display.clear();
		img.draw();
		img2.draw();
		display.swap();

	}

	Display::quit();

	return 0;

}