#include "pch.h"
#include "Move.h"

Move::Move(const Position& from, const Position& to) {
	this->from = from;
	this->to = to;
}
