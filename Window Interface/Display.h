#pragma once

#include <string>

class Display {
public:

	Display();
	Display(int width, int height, const std::string& title);
	Display(int width, int height);
	Display(const std::string& title);

	//Poll and handle all window events
	static void poll();

	//Close display
	void close();
	//Cleanup library initializations (SDL/GLEW)
	static void quit();
	//Clear and set color
	void clear(float r, float g, float b, float a);
	//Clear GL buffer
	void clear();
	//Swap buffers
	void swap();
	//Set display title
	void setTitle(const std::string&);
	//Set display to fullscreen mode
	void setFullscreen(bool);
	//Change size of display
	void setSize(int w, int h);
	//Center display in center of monitor
	void center();
	//Hide cursor in display
	void hideCursor(bool);
	//Lock cursor in display
	void relativeCursor(bool);
	//Makes display current GL recipient
	void makeCurrent();

	//Is display currently open
	bool isOpen();

private:

	void* glContext = nullptr;
	void* window = nullptr;

};