#include "Display.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "DisplayEvent.h"

#include <SDL/SDL.h>
#undef main
#include <GL/glew.h>
#include <map>
#include <time.h>

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
//System cursor array
static SDL_Cursor* systemCursors[(int)CURSORTYPE::NUM_CURSORS] = { nullptr };
static Display* mainDisplay = nullptr;
static float framesPerSecond = 0.0f;
static float delta = 0.0f;

Display::Display() : Display(DEFAULT_SIZE[0], DEFAULT_SIZE[1], DEFAULT_NAME) {}

Display::Display(int width, int height) : Display(width, height, DEFAULT_NAME) {}

Display::Display(const std::string& title) : Display(DEFAULT_SIZE[0], DEFAULT_SIZE[1], title) {}

Display::Display(int width, int height, const std::string& title) {

	if (!sdl_init && SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		sdl_init = true;
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return;
	}

	if (systemCursors[0] == nullptr) {
		for (int i = 0; i < (int)CURSORTYPE::NUM_CURSORS; ++i) {
			systemCursors[i] = SDL_CreateSystemCursor((SDL_SystemCursor)i);
		}
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

	screenWidth = 2.0f * width / height;
	pxToScreen = glm::vec2(screenWidth / width, 2.0f / height);

}

Display::~Display() {

	if (mainDisplay == this) {
		mainDisplay = nullptr;
		if (windowMap.begin() != windowMap.end()) {
			windowMap.begin()->second->makeMain();
		}
	}

}

glm::vec2 Display::getPixelToScreen() {

	return pxToScreen;

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

void Display::refreshScreenSize() {

	int w, h;
	SDL_GetWindowSize((SDL_Window*)window, &w, &h);
	DisplayResizeEvent evt(w, h);
	this->sendEvent(&evt);

}

void Display::setSize(int w, int h) {

	w = abs(w);
	h = abs(h);
	SDL_SetWindowSize((SDL_Window*)window, w, h);
	MAKE_CURRENT();
	glViewport(0, 0, w, h);
	DisplayResizeEvent evt(w, h);
	this->sendEvent(&evt);

}

void Display::setResizable(bool toggle) {
	SDL_SetWindowResizable((SDL_Window*)window, (SDL_bool)toggle);
}

void Display::setPosition(int x, int y) {
	SDL_SetWindowPosition((SDL_Window*)window, x, y);
}

void Display::setCursor(CURSORTYPE t) {

	SDL_SetCursor(systemCursors[(int)t]);

}

void Display::center() {
	setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Display::hideCursor(bool toggle) {
	SDL_ShowCursor(toggle ? 0 : 1);
}

void Display::relativeCursor(bool toggle) {
	SDL_SetRelativeMouseMode(toggle ? SDL_TRUE : SDL_FALSE);
}

glm::vec2 Display::getSize() {

	int w, h;
	SDL_GetWindowSize((SDL_Window*)window, &w, &h);
	return glm::vec2(w, h);

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
			case SDL_WINDOWEVENT_CLOSE: {
				disp.close();
				break;
			}
			case SDL_WINDOWEVENT_RESIZED: {
				disp.makeCurrent();
				glm::vec2 size = disp.getSize();
				disp.screenWidth = 2.0f * size.x / size.y;
				disp.pxToScreen = glm::vec2(disp.screenWidth, 2.0f) / size;
				DisplayResizeEvent evt(e.window.data1, e.window.data2);
				disp.sendEvent(&evt);
				break;
			}
			}
			break;
		}
		case SDL_KEYDOWN: {

			KEY k = KeyboardEvent::SDL_to_Key((int)e.key.keysym.sym);
			if (!KeyboardEvent::isKeyDown(k)) {
				KeyboardEvent::noteKey(k, true);
				KeyboardEvent evt(k, true);
				disp.sendEvent(&evt);
			}
			break;
		}
		case SDL_KEYUP: {
			KEY k = KeyboardEvent::SDL_to_Key((int)e.key.keysym.sym);
			if (KeyboardEvent::isKeyDown(k)) {
				KeyboardEvent::noteKey(k, false);
				KeyboardEvent evt(k, false);
				disp.sendEvent(&evt);
			}
			break;
		}
		case SDL_MOUSEMOTION: {
			glm::vec2 motion(e.motion.x, e.motion.y);
			MouseMotionEvent evt(motion, e.motion.xrel, e.motion.yrel);
			disp.sendEvent(&evt);
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			glm::vec2 pt(e.button.x, e.button.y);
			disp.rawCoordToScreen(pt);
			MouseButtonEvent evt(pt, true, e.button.button - 1);
			disp.sendEvent(&evt);
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			glm::vec2 pt(e.button.x, e.button.y);
			disp.rawCoordToScreen(pt);
			MouseButtonEvent evt(pt, false, e.button.button - 1);
			disp.sendEvent(&evt);
			break;
		}
		}

	}

	//Update time & send frame event to all displays
	static clock_t lastFrame = clock();
	delta = (float)(clock() - lastFrame) / CLOCKS_PER_SEC;
	framesPerSecond = 1.0f / delta;
	DisplayFrameEvent evt(delta);
	lastFrame = clock();
	std::map<Uint32, Display*>::iterator it = windowMap.begin();
	for (; it != windowMap.end(); ++it) {
		it->second->sendEvent(&evt);
	}

}

float Display::getFPS() {

	return framesPerSecond;

}

float Display::getDelta() {

	return delta;

}

bool Display::isOpen() {
	
	return window != nullptr;

}

glm::vec2 Display::getScreenSpace() {

	return glm::vec2(screenWidth, 2.0f);

}

void Display::rawCoordToScreen(glm::vec2& pt) {

	pt *= pxToScreen;
	pt.x /= screenWidth * 0.5f;
	pt.x -= 1.0f;
	pt.y = -pt.y + 1.0f;

}