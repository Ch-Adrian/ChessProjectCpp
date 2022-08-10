#include "pch.h"
#include "Queen.h"
#include "Settings.h"

Queen::Queen(int type, int color): Piece(type, color) {
	if (color == WHITE) {
		this->image_source = "resources/white_queen.bmp";
	}
	else {
		this->image_source = "resources/black_queen.bmp";
	}
}

bool Queen::validate_move(const Move& move){
	return false;
}

std::vector<Position> Queen::get_available_positions(const Position& pos) {
	std::vector<Position> emptyVector;
	return emptyVector;
}

std::string Queen::get_image_source() {
	return this->image_source;
}



