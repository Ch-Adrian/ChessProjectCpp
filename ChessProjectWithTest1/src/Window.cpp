#include "pch.h"
#include "Window.h"
#include <iostream>
#include "InitializationException.h"
#include "NullPointerException.h"


Window::Window(const std::string title, const int width, const int height)
	:width(width), title(title), height(height), mouseFocus(true), keyboardFocus(true), fullScreen(false), minimized(false)
{
	initWindow();
	initRenderer();
}

void Window::initWindow() {
	this->window = SDL_CreateWindow(&title[0], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (this->window == NULL) {
		throw InitializationException(&std::string("Window could not be created! SDL Error: " +
			std::string(SDL_GetError()) +
			"\n")[0]);
	}
}

void Window::initRenderer() {

	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->renderer == NULL) {
		throw InitializationException(&std::string("Renderer could not be created! SDL Error: " + std::string(SDL_GetError()) + "\n")[0]);
	}
	else {
		SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
}

Window::~Window() {

	if (this->renderer != NULL) SDL_DestroyRenderer(this->renderer);
	if (this->window != NULL) SDL_DestroyWindow(this->window);

	std::string title = "";
	int width = 0;
	int height = 0;
	bool mouseFocus = false;
	bool keyboardFocus = false;
	bool fullScreen = false;
	bool minimized = false;
}

void Window::handleEvent(SDL_Event& event) {

	if (event.type == SDL_WINDOWEVENT) {
		switch (event.window.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			this->width = event.window.data1;
			this->height = event.window.data2;
			SDL_RenderPresent(this->renderer);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(this->renderer);
			break;
		case SDL_WINDOWEVENT_ENTER:
			this->mouseFocus = true;
			break;
		case SDL_WINDOWEVENT_LEAVE:
			this->mouseFocus = false;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			this->keyboardFocus = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			this->keyboardFocus = false;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			this->minimized = true;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			this->minimized = false;
			break;
		case SDL_WINDOWEVENT_RESTORED:
			this->minimized = false;
			break;
		}
	}
}

int Window::getWidth() {
	return this->width;
}

int Window::getHeight() {
	return this->height;
}

SDL_Renderer* Window::getRenderer() const {
	return this->renderer;
}

bool Window::hasMouseFocus() {
	return this->mouseFocus;
}

bool Window::hasKeyboardFocus() {
	return this->keyboardFocus;
}

bool Window::isMinimized() {
	return this->minimized;
}

