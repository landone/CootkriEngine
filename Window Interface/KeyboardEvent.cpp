#include "KeyboardEvent.h"

#include <map>
#include <list>
#include <algorithm>
#include <SDL/SDL_keycode.h>

static std::list<KeyboardListener*> listeners;
static bool keyDown[(int)KEY::MAX_KEYS] = { false };

static std::map<SDL_Keycode, KEY> KEYMAP;
static const std::string CHARMAP[(int)KEY::MAX_KEYS] = {
	"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
	"ESCAPE", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
	"`", "-", "=", "BACKSPACE", "\t", "[", "]", "\\",
	"CAPSLOCK", ";", "'", "\n", "LSHIFT", ",", ".", "/", "RSHIFT",
	"LCTRL", "LALT", " ", "RALT", "RCTRL", "LEFT", "UP", "DOWN", "RIGHT",
	"INSERT", "HOME", "PAGEUP", "DELETE", "END", "PAGEDOWN"
};

KeyboardListener::KeyboardListener() {

	listeners.push_back(this);

}

KeyboardListener::~KeyboardListener() {

	listeners.erase(std::remove(listeners.begin(), listeners.end(), this), listeners.end());

}

bool KeyboardListener::isKeyDown(KEY k) {

	return keyDown[(int)k];

}

void KeyboardEvent::sendKeyPress(KEY k) {

	keyDown[(int)k] = true;

	std::list<KeyboardListener*>::iterator it;
	for (it = listeners.begin(); it != listeners.end(); it++) {
		(*it)->onKeyPress(k);
	}

}

void KeyboardEvent::sendKeyRelease(KEY k) {

	keyDown[(int)k] = false;

	std::list<KeyboardListener*>::iterator it;
	for (it = listeners.begin(); it != listeners.end(); it++) {
		(*it)->onKeyRelease(k);
	}

}

void populateKeyMap() {

	KEYMAP[SDLK_0] = KEY::N_0;
	KEYMAP[SDLK_1] = KEY::N_1;
	KEYMAP[SDLK_2] = KEY::N_2;
	KEYMAP[SDLK_3] = KEY::N_3;
	KEYMAP[SDLK_4] = KEY::N_4;
	KEYMAP[SDLK_5] = KEY::N_5;
	KEYMAP[SDLK_6] = KEY::N_6;
	KEYMAP[SDLK_7] = KEY::N_7;
	KEYMAP[SDLK_8] = KEY::N_8;
	KEYMAP[SDLK_9] = KEY::N_9;

	KEYMAP[SDLK_a] = KEY::A;
	KEYMAP[SDLK_b] = KEY::B;
	KEYMAP[SDLK_c] = KEY::C;
	KEYMAP[SDLK_d] = KEY::D;
	KEYMAP[SDLK_e] = KEY::E;
	KEYMAP[SDLK_f] = KEY::F;
	KEYMAP[SDLK_g] = KEY::G;
	KEYMAP[SDLK_h] = KEY::H;
	KEYMAP[SDLK_i] = KEY::I;
	KEYMAP[SDLK_j] = KEY::J;
	KEYMAP[SDLK_k] = KEY::K;
	KEYMAP[SDLK_l] = KEY::L;
	KEYMAP[SDLK_m] = KEY::M;
	KEYMAP[SDLK_n] = KEY::N;
	KEYMAP[SDLK_o] = KEY::O;
	KEYMAP[SDLK_p] = KEY::P;
	KEYMAP[SDLK_q] = KEY::Q;
	KEYMAP[SDLK_r] = KEY::R;
	KEYMAP[SDLK_s] = KEY::S;
	KEYMAP[SDLK_t] = KEY::T;
	KEYMAP[SDLK_u] = KEY::U;
	KEYMAP[SDLK_v] = KEY::V;
	KEYMAP[SDLK_w] = KEY::W;
	KEYMAP[SDLK_x] = KEY::X;
	KEYMAP[SDLK_y] = KEY::Y;
	KEYMAP[SDLK_z] = KEY::Z;

	KEYMAP[SDLK_ESCAPE] = KEY::ESCAPE;
	KEYMAP[SDLK_F1] = KEY::F1;
	KEYMAP[SDLK_F2] = KEY::F2;
	KEYMAP[SDLK_F3] = KEY::F3;
	KEYMAP[SDLK_F4] = KEY::F4;
	KEYMAP[SDLK_F5] = KEY::F5;
	KEYMAP[SDLK_F6] = KEY::F6;
	KEYMAP[SDLK_F7] = KEY::F7;
	KEYMAP[SDLK_F8] = KEY::F8;
	KEYMAP[SDLK_F9] = KEY::F9;
	KEYMAP[SDLK_F10] = KEY::F10;
	KEYMAP[SDLK_F11] = KEY::F11;
	KEYMAP[SDLK_F12] = KEY::F12;

	KEYMAP[SDLK_TAB] = KEY::TAB;
	KEYMAP[SDLK_BACKQUOTE] = KEY::BACKQUOTE;
	KEYMAP[SDLK_MINUS] = KEY::MINUS;
	KEYMAP[SDLK_EQUALS] = KEY::EQUALS;
	KEYMAP[SDLK_BACKSPACE] = KEY::BACKSPACE;
	KEYMAP[SDLK_TAB] = KEY::TAB;
	KEYMAP[SDLK_LEFTBRACKET] = KEY::LEFTBRACKET;
	KEYMAP[SDLK_RIGHTBRACKET] = KEY::RIGHTBRACKET;
	KEYMAP[SDLK_BACKSLASH] = KEY::BACKSLASH;

	KEYMAP[SDLK_CAPSLOCK] = KEY::CAPSLOCK;
	KEYMAP[SDLK_SEMICOLON] = KEY::SEMICOLON;
	KEYMAP[SDLK_QUOTE] = KEY::APOSTROPHE;
	KEYMAP[SDLK_RETURN] = KEY::RETURN;
	KEYMAP[SDLK_LSHIFT] = KEY::LSHIFT;
	KEYMAP[SDLK_COMMA] = KEY::COMMA;
	KEYMAP[SDLK_PERIOD] = KEY::PERIOD;
	KEYMAP[SDLK_SLASH] = KEY::FORWARDSLASH;
	KEYMAP[SDLK_RSHIFT] = KEY::RSHIFT;

	KEYMAP[SDLK_LCTRL] = KEY::LCTRL;
	KEYMAP[SDLK_LALT] = KEY::LALT;
	KEYMAP[SDLK_SPACE] = KEY::SPACEBAR;
	KEYMAP[SDLK_RALT] = KEY::RALT;
	KEYMAP[SDLK_RCTRL] = KEY::RCTRL;
	KEYMAP[SDLK_LEFT] = KEY::LEFT;
	KEYMAP[SDLK_UP] = KEY::UP;
	KEYMAP[SDLK_DOWN] = KEY::DOWN;
	KEYMAP[SDLK_RIGHT] = KEY::RIGHT;

	KEYMAP[SDLK_INSERT] = KEY::INSERT;
	KEYMAP[SDLK_HOME] = KEY::HOME;
	KEYMAP[SDLK_PAGEUP] = KEY::PAGEUP;
	KEYMAP[SDLK_DELETE] = KEY::DELETE;
	KEYMAP[SDLK_END] = KEY::END;
	KEYMAP[SDLK_PAGEDOWN] = KEY::PAGEDOWN;

}

KEY KeyboardEvent::SDL_to_Key(int sdl) {

	if (KEYMAP.empty()) {
		populateKeyMap();
	}

	return KEYMAP[sdl];

}

std::string KeyboardListener::keyToString(KEY k) {

	return CHARMAP[(int)k];

}