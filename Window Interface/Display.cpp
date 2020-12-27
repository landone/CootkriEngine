#include "Display.h"
#include "KeyboardEvent.h"

#include <SDL/SDL.h>
#undef main
#include <GL/glew.h>
#include <map>

#define MAKE_CURRENT() (SDL_GL_MakeCurrent((SDL_Window*)window, glContext));

static const char* DEFAULT_NAME = "Display";
static const int DEFAULT_SIZE[2] = { 1600, 900 };
static const int BUFFER_SIZE = 32;
static const int COLOR_SIZE = BUFFER_SIZE / 4;
static const int DEPTH_SIZE = 16;

static bool sdl_init = false;
static bool glew_init = false;
//Map window ID to display
static std::map<Uint32, Display*> windowMap;
static Display* mainDisplay = nullptr;

Display::Display() : Display(DEFAULT_SIZE[0], DEFAULT_SIZE[1], DEFAULT_NAME) {}

Display::Display(int width, int height) : Display(width, height, DEFAULT_NAME) {}

Display::Display(const std::string& title) : Display(DEFAULT_SIZE[0], DEFAULT_SIZE[1], title) {}

Display::Display(int width, int height, const std::string& title) {

	if (!sdl_init && SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		sdl_init = true;
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
	MAKE_CURRENT();

	if (!glew_init) {
		GLenum status = glewInit();
		if (status != GLEW_OK) {
			printf("glewInit Error\n");
			return;
		}
		glew_init = true;
	}

	/* Default GL settings */
	glViewport(0, 0, width, height);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	windowMap[SDL_GetWindowID((SDL_Window*)window)] = this;

	if (!mainDisplay) {
		mainDisplay = this;
	}

}

Display::~Display() {

	if (mainDisplay == this) {
		mainDisplay = nullptr;
		if (windowMap.begin() != windowMap.end()) {
			windowMap.begin()->second->makeMain();
		}
	}

}

void Display::makeCurrent() {
	MAKE_CURRENT();
}

void Display::makeMain() {
	mainDisplay = this;
}

Display* Display::getMain() {
	return mainDisplay;
}

void Display::close() {

	if (glContext) {
		SDL_GL_DeleteContext(glContext);
		glContext = nullptr;
	}
	if (window) {
		windowMap.erase(SDL_GetWindowID((SDL_Window*)window));
		SDL_DestroyWindow((SDL_Window*)window);
		window = nullptr;
	}

}

void Display::quit() {
	if (sdl_init) {
		sdl_init = false;
		SDL_Quit();
	}
}

void Display::clear(float r, float g, float b, float a) {

	MAKE_CURRENT();
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Display::clear() {

	MAKE_CURRENT();
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
	MAKE_CURRENT();
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

void Display::swap() {

	MAKE_CURRENT();
	SDL_GL_SwapWindow((SDL_Window*)window);

}

void Display::poll() {

	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		std::map<Uint32, Display*>::iterator it = windowMap.find(e.window.windowID);
		if (it == windowMap.end()) {
			continue;
		}
		Display& disp = *(it->second);

		switch (e.type) {
		case SDL_WINDOWEVENT: {
			switch (e.window.event) {
			case SDL_WINDOWEVENT_CLOSE:
				disp.close();
			}
			break;
		}
		case SDL_KEYDOWN: {

			KEY k = KeyboardEvent::SDL_to_Key((int)e.key.keysym.sym);
			KeyboardEvent evt(k, true);
			disp.sendEvent(&evt);
			break;
		}
		case SDL_KEYUP: {
			KEY k = KeyboardEvent::SDL_to_Key((int)e.key.keysym.sym);
			KeyboardEvent evt(k, false);
			disp.sendEvent(&evt);
			break;
		}
		}

	}

}

bool Display::isOpen() {
	
	return window != nullptr;

}