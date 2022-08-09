#pragma once
#include "Position.h"

class Piece
{
private:
	int type;
	bool color;

public:

	Piece(int type, bool color);
	//virtual bool validate_move(Position* from, Position* to);
	int get_type();
	bool get_color();
};

