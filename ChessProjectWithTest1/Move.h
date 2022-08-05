#pragma once
#include "Position.h"

class Move
{
public:
	Position* from;
	Position* to;

	Move(Position* from, Position* to);
};

