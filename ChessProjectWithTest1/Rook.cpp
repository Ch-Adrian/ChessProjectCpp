#include "pch.h"
#include "Rook.h"
#include "Settings.h"

Rook::Rook(int type, int color): Piece(type, color) {
	if (color == WHITE) {
		this->image_source = "resources/white_rook.bmp";
	}
	else {
		this->image_source = "resources/black_rook.bmp";
	}
}

bool Rook::validate_move(const Move& move){
	return false;
}

std::vector<Position> Rook::get_available_positions(const Position& pos) {
	std::vector<Position> emptyVector;
	return emptyVector;

}

std::string Rook::get_image_source() {
	return this->image_source;
}




