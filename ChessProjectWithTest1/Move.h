#pragma once
#include "Position.h"

class Move
{
public:
	Position from;
	Position to;

	Move();
	Move(const Position& from, const Position& to);
	Move(const Move& mv);
	Move& operator=(const Move& mv);
	bool operator==(const Move& mv);
};

