#pragma once

#include <string>

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

class Evt_Keyboard {
public:

	static void sendKeyPress(KEY);
	static void sendKeyRelease(KEY);

	static KEY SDL_to_Key(int);

};

class Keyboard_Listener {
public:
	Keyboard_Listener();
	~Keyboard_Listener();
protected:
	static bool isKeyDown(KEY);
	static std::string keyToString(KEY);
private:

	friend Evt_Keyboard;
	virtual void onKeyPress(KEY) {};
	virtual void onKeyRelease(KEY) {};

};