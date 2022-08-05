#pragma once
#include "Position.h"

class Piece
{
private:
	int type;
	bool color;

public:

	Piece(int type, bool color);
	int get_type();
	bool get_color();
};

