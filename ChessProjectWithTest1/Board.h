#pragma once
#include "Field.h"
#include "Piece.h"

class Board
{
private:
	
	SDL_Renderer* renderer;

	Field** array_of_fields;
	Field** array_of_pieces;
	int board_width_px;
	int board_height_px;
	int field_width_px;
	int field_height_px;

public:

	Board(SDL_Renderer* renderer,
			std::map<std::pair<int, int>, Piece*> pieces);
	~Board();
	void render_board(SDL_Renderer* renderer);
	void change_position(int row, int col, int x_px, int y_px);
	void drag_piece(int row, int col, int destination_x, int destination_y);
};