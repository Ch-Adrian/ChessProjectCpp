#pragma once
#include "SdlIncludes.h"
#include "InitializationException.h"

class Window
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::string title;
	int width;
	int height;

	bool mouseFocus;
	bool keyboardFocus;
	bool fullScreen;
	bool minimized;

	void initWindow();
	void initRenderer();

public:
	Window(const std::string title, const int width, const int height); 
	~Window();
	void handleEvent(SDL_Event& e);

	int getWidth();
	int getHeight();
	SDL_Renderer* getRenderer() const;

	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
};

