#pragma once
#include "Position.h"
#include "Move.h"

class Piece
{
private:
	int type;
	bool color;

public:

	Piece(int type, bool color);

	virtual bool validate_move(const Move& move) = 0;
	virtual std::vector<Position> get_available_positions(const Position& pos) = 0;
	virtual std::string get_image_source() = 0;

	//virtual bool validate_move(Position* from, Position* to);
	int get_type();
	bool get_color();
};

