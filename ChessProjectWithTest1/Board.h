#pragma once
#include "Field.h"
#include "Piece.h"
#include "BoardData.h"

class Board
{
private:

	SDL_Renderer* renderer;

	Field** array_of_fields;
	Field** array_of_pieces;

	std::vector<Picture*> ordered_picture_pieces;

public:

	BoardData boardData;

	Board(SDL_Renderer* renderer);
	~Board();
	void render_board();
	void drag_piece(int row, int col, int destination_x, int destination_y);
	void apply_pieces(std::map<Position, Piece*> pieces);
	void mark_accesible_fields(std::vector<Position> available_positions);
	void clean_light();
};