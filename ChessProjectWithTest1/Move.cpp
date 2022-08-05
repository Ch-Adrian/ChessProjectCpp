#include "pch.h"
#include "Move.h"

Move::Move(Position* from, Position* to) {
	this->from = from;
	this->to = to;
}
