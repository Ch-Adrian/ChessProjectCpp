#pragma once
#include "Field.h"
#include "Piece.h"
#include "BoardData.h"
#include "Window.h"

class Board
{
private:

	SDL_Renderer* renderer;
	Window& mainWindow;

	Field** array_of_fields;
	Field** array_of_pieces;

	std::vector<Picture*> ordered_picture_pieces;

	Picture picture_black_queen;
	Picture picture_white_queen;
	Picture picture_black_knight;
	Picture picture_white_knight;
	Picture picture_background;
	Picture picture_background2;

	BoardData boardData;

public:

	Board(Window &mainWindow);
	~Board();
	void render_board();
	void render_selection(PlayerColor exchange_color);
	void drag_piece(int row, int col, int destination_x, int destination_y);
	void drag_piece(Position pos, AbsolutePosition abs_pos);
	void apply_pieces();
	void mark_accesible_fields(int moving_picture_init_col, int moving_picture_init_row);
	void clean_light();
	void exchange_pawn(bool isQueen, PlayerColor exchange_color);
	int move_piece(const Move& move);
	bool validate_move(const Move& move);

};