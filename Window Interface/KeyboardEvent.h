#pragma once

#include "Event.h"

#include <string>

class Display;

enum class KEY {
	N_0, N_1, N_2, N_3, N_4, N_5, N_6, N_7, N_8, N_9,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	ESCAPE, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	BACKQUOTE, MINUS, EQUALS, BACKSPACE, TAB, LEFTBRACKET, RIGHTBRACKET, BACKSLASH,
	CAPSLOCK, SEMICOLON, APOSTROPHE, RETURN, LSHIFT, COMMA, PERIOD, FORWARDSLASH, RSHIFT,
	LCTRL, LALT, SPACEBAR, RALT, RCTRL, LEFT, UP, DOWN, RIGHT,
	INSERT, HOME, PAGEUP, DELETE, END, PAGEDOWN,
	MAX_KEYS
};

//Display listener for keyboard input
class KeyboardEvent : public Event {
public:

	KeyboardEvent(KEY k, bool press);

	KEY key;
	bool press;

	//Is key currently pressed
	static bool isKeyDown(KEY);
	//Convert key enum to string representation
	static std::string keyToString(KEY);
private:
	friend Display;
	//Convert SDL keycode to KEY enum
	static KEY SDL_to_Key(int);
	//Remember if a key is down or not
	static void noteKey(KEY, bool press);
};