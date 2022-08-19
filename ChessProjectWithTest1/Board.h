#pragma once
#include "Field.h"
#include "Piece.h"

class Board
{
private:
	
	SDL_Renderer* renderer;

	Field** array_of_fields;
	Field** array_of_pieces;

public:

	Board(SDL_Renderer* renderer,
			std::map<Position, Piece*> pieces);
	~Board();
	void render_board();
	void change_position(int col, int row, int to_x_px, int to_y_px);
	void drag_piece(int row, int col, int destination_x, int destination_y);
};