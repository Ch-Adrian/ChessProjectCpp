#pragma once
#include "Piece.h"
#include "Move.h"

class Pawn: public Piece
{
	std::string image_source;
	bool firstMove;

public:

	Pawn(int type, int color);
	virtual bool validate_move(IShareBoardData& share, const Move& move);
	virtual std::vector<Position> get_available_positions(IShareBoardData& share, const Position& pos);
	virtual std::vector<Position> get_positions_under_attack(IShareBoardData& share, const Position& pos);
	virtual std::string get_image_source();
	void make_first_move();

};






