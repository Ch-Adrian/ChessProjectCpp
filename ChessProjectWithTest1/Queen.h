#pragma once
#include "Piece.h"
#include "Move.h"

class Queen: public Piece
{
	std::string image_source;

public:

	Queen(int type, int color);
	virtual bool validate_move(const Move& move);
	virtual std::vector<Position> get_available_positions(const Position& pos);
	virtual std::string get_image_source();

};


