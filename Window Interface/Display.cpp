#include "Display.h"

#include <SDL/SDL.h>
#undef main
#include <GL/glew.h>

static const char* DEFAULT_NAME = "Display";
static const int DEFAULT_SIZE[2] = { 1600, 900 };
static const int BUFFER_SIZE = 32;
static const int COLOR_SIZE = BUFFER_SIZE / 4;
static const int DEPTH_SIZE = 16;

Display::Display() : Display(DEFAULT_SIZE[0], DEFAULT_SIZE[1], DEFAULT_NAME) {}

Display::Display(int width, int height) : Display(width, height, DEFAULT_NAME) {}

Display::Display(const std::string& title) : Display(DEFAULT_SIZE[0], DEFAULT_SIZE[1], title) {}

Display::Display(int width, int height, const std::string& title) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return;
	}

	/* Prepare buffers */
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, COLOR_SIZE);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, COLOR_SIZE);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, COLOR_SIZE);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, COLOR_SIZE);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, BUFFER_SIZE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, DEPTH_SIZE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	/* Create window & context */
	SDL_DisplayMode dmode;
	SDL_GetCurrentDisplayMode(0, &dmode);
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext((SDL_Window*)window);

	GLenum status = glewInit();
	if (status != GLEW_OK) {
		printf("glewInit Error\n");
		return;
	}

	/* Default GL settings */
	glViewport(0, 0, width, height);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

}

void Display::close() {

	SDL_GL_DeleteContext(glContext);
	glContext = nullptr;
	SDL_DestroyWindow((SDL_Window*)window);
	window = nullptr;
	SDL_Quit();

}

void Display::clear(float r, float g, float b, float a) {

	glClearColor(r, g, b, a);
	clear();

}

void Display::clear() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Display::setTitle(const std::string& title)
{
	SDL_SetWindowTitle((SDL_Window*)window, title.c_str());
}

void Display::setFullscreen(bool toggle) {
	SDL_SetWindowFullscreen((SDL_Window*)window, toggle ? SDL_WINDOW_FULLSCREEN : 0);
}

void Display::setSize(int w, int h) {

	w = abs(w);
	h = abs(h);
	SDL_SetWindowSize((SDL_Window*)window, w, h);
	glViewport(0, 0, w, h);

}

void Display::center() {
	SDL_SetWindowPosition((SDL_Window*)window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Display::hideCursor(bool toggle) {
	SDL_ShowCursor(toggle ? 0 : 1);
}

void Display::relativeCursor(bool toggle) {
	SDL_SetRelativeMouseMode(toggle ? SDL_TRUE : SDL_FALSE);
}

void Display::update() {

	SDL_GL_SwapWindow((SDL_Window*)window);
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			close();
			break;
		}

	}

}

bool Display::isOpen() {
	
	return window != nullptr;

}