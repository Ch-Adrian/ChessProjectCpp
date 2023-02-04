#pragma once
#include "Field.h"
#include "Piece.h"
#include "Move.h"
#include "IShareBoardData.h"

class BoardData: public IShareBoardData
{

private:
	std::vector<Piece*> white_pieces;
	std::vector<Piece*> black_pieces;
	std::vector<Piece*> additional_pieces;

	std::map<Position, Piece*> board;
	Piece*** boardArray;

	Move pawn_double_move;
	Position edge_pawn_position;

public:

	BoardData();
	virtual const std::map<Position, Piece*> get_board();
	virtual Piece*** get_array_board();
	virtual Piece* get_piece(const Position& pos);
	virtual int get_type(const Position& pos);
	virtual int get_color(const Position& pos);
	virtual const Move& get_last_pawn_move();
	virtual const std::vector<Piece*> get_one_side_pieces(PlayerColor side);
	int move_piece(const Move& move);
	bool validate_move(const Move& move);
	void exchange_pawn(int type, PlayerColor color);
	std::vector<Position> get_all_available_positions(const Position& pos);

	~BoardData();
};

