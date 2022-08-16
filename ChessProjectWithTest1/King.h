#pragma once
#include "Piece.h"
#include "Move.h"

class King: public Piece
{
	std::string image_source;

public:

	King(int type, int color);
	virtual bool validate_move(IShareBoardData& share, const Move& move);
	virtual std::vector<Position> get_available_positions(IShareBoardData& share, const Position& pos);
	virtual std::string get_image_source();
	bool checkmate();
};

