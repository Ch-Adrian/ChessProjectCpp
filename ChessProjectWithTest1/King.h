#pragma once
#include "Piece.h"

class King: public Piece
{
public:
	virtual bool validate_move(Position* from, Position* to);
	virtual std::string get_image_source();
};

