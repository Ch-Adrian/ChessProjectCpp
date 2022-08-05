#pragma once
#include "Field.h"

class Board
{
private:

	Field** array_of_fields;
	Field** array_of_pieces;
	int board_width_px;
	int board_height_px;
	int field_width_px;
	int field_height_px;

public:

	Board(int board_width_px, int board_height_px,
		int field_width_px, int field_height_px,
		SDL_Renderer* renderer,
		SDL_PixelFormat* format,
			std::map<std::pair<int, int>, std::pair<int, bool>> pieces);
	~Board();
	void render_board(SDL_Renderer* renderer);
	void change_position(int row, int col, int x_px, int y_px);
};