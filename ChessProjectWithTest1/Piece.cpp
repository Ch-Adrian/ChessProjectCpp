#include "pch.h"
#include "Piece.h"

Piece::Piece(PieceType type, PlayerColor color) {
	this->color = color;
	this->type = type;
	this->id = -1;
}

PieceType Piece::get_type() {
	return this->type;
}

PlayerColor Piece::get_color() {
	return this->color;
}

int Piece::get_id() {
	return this->id;
}

void Piece::set_id(int id) {
	this->id = id;
}

bool Piece::position_inside_board(const Position& pos) {
	if (pos.col <= 8 && pos.col >= 1) {
		if (pos.row <= 8 && pos.row >= 1) {
			return true;
		}
	}
	return false;
}