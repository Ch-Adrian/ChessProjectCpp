#pragma once

#include "Board.h"
#include "Window.h"

class ApplicationView {
public:

	const static int BOARD_WIDTH = 850;
	const static int BOARD_HEIGHT = 850;
	const static int FIELD_WIDTH = 100;
	const static int FIELD_HEIGHT = 100;
	const static int BOARD_BORDER_WIDTH = 25;

	Window mainWindow;
	Board board;

	Picture picture_black_queen;
	Picture picture_white_queen;
	Picture picture_black_knight;
	Picture picture_white_knight;
	Picture picture_background;
	Picture picture_background2;

	bool onDrag = false;
	int moving_picture_init_col = -1;
	int moving_picture_init_row = -1;

	SDL_Rect originViewPort;
	bool show_middleViewPort = false;
	SDL_Rect middleViewPort;
	bool exchange_color = false;

	ApplicationView();

	bool handleEvent(SDL_Event& event);
	void renderView();

	void actionClick(SDL_Event& event);
	bool actionRelease(SDL_Event& event);
	void actionDrag(SDL_Event& event);

};