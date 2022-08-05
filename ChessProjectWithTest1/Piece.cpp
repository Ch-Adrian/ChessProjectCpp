#include "pch.h"
#include "Piece.h"

Piece::Piece(int type, bool color) {
	this->color = color;
	this->type = type;
}

int Piece::get_type() {
	return this->type;
}

bool Piece::get_color() {
	return this->color;
}
