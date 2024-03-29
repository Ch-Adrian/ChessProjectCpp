#include "pch.h"
#include "Move.h"

Move::Move(const Position& from, const Position& to) {
	this->from = from;
	this->to = to;
}

Move::Move() {}

Move::Move(const Move& mv) {
	this->from = mv.from;
	this->to = mv.to;
}

Move& Move::operator=(const Move& mv) {
	this->from = mv.from;
	this->to = mv.to;
	return *this;
}

bool Move::operator==(const Move& mv) {
	return (this->from == mv.from && this->to == mv.to);
}

bool Move::isEmpty() const{
	if (this->from.isEmpty() && this->to.isEmpty()) {
		return true;
	}
	return false;
}

bool Move::isBackToTheSamePlace() {
	return this->from == this->to;
}
