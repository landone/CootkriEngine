#pragma once

#include "Event.h"

#include <glm/vec2.hpp>

#include <string>
#include <list>

enum class CURSORTYPE {
	ARROW, IBEAM, WAIT, CROSSHAIR, WAITARROW,
	NWSE, NESW, WE, NS, SIZEALL, NO, HAND, NUM_CURSORS
};

class Display : public EventManager {
public:

	Display();
	~Display();
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
	//Set position of display
	void setPosition(int, int);
	//Change size of display
	void setSize(int w, int h);
	//Allow resizing window
	void setResizable(bool);
	//Center display in center of monitor
	void center();
	//Set cursor type
	void setCursor(CURSORTYPE);
	//Hide cursor in display
	void hideCursor(bool);
	//Lock cursor in display
	void relativeCursor(bool);
	//Makes display current GL recipient
	void makeCurrent();
	//Set as main display
	void makeMain();
	//Get ratio of pixels to screen units
	glm::vec2 getPixelToScreen();
	//Get window size
	glm::vec2 getSize();
	//Get relative screen space boundaries
	glm::vec2 getScreenSpace();

	//Is display currently open
	bool isOpen();
	//Retrieve main display
	static Display* getMain();

private:

	void* glContext = nullptr;
	void* window = nullptr;
	//Not in pixels, but screen coordinates
	float screenWidth = 2.0f;
	glm::vec2 pxToScreen = glm::vec2(1,1);

	//Convert raw window coordinates to screen coordinates
	void rawCoordToScreen(glm::vec2& coords);

};