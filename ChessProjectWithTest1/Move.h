#pragma once
#include "Position.h"

class Move
{
public:
	Position from;
	Position to;

	Move(const Position& from, const Position& to);
};

