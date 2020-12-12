#pragma once

#include <string>

class Display {
public:

	Display();
	Display(int width, int height, const std::string& title);
	Display(int width, int height);
	Display(const std::string& title);

	void close();
	void clear(float r, float g, float b, float a);
	void clear();
	void update();
	void setTitle(const std::string&);
	void setFullscreen(bool);
	void setSize(int w, int h);
	void center();
	void hideCursor(bool);
	void relativeCursor(bool);


	bool isOpen();

private:

	void* glContext = nullptr;
	void* window = nullptr;

};